#include "ConnectionManager.h"

#include "../protocol/Encryption.h"
#include "../protocol/PrimaryHandler.h"
#include "../protocol/RoomName.h" // temp include for forcing chat client connection here
#include "../protocol/SecondaryHandler.h"

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/read.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>

namespace OpenMX {

ConnectionManager::ConnectionManager()
    : m_primary(PrimaryHandler())
    , m_secondary(SecondaryHandler())
{
    std::cout << "Constructor of ConnectionManager" << std::endl;
    timer.async_wait([&](boost::system::error_code ec) {
        tick(ec);
    });
    m_mainThread = new std::thread([&]() {
        m_context.run();
    });
}

void ConnectionManager::dropConnection(Connection& connection)
{
    connection.socket.close();
}

void ConnectionManager::handleIncoming(tcp::socket&& socket, tcp::endpoint& remoteEndPoint)
{
    // handleIncoming must be called from an io_context thread
    assert(m_context.get_executor().running_in_this_thread());

    // TODO: check max connections
    // TODO: check ban list

    // Setup a connection structure for tracking and send to handshake to determine connection type
    Connection& connection = m_connections.emplace_back(std::move(socket), remoteEndPoint);

    boost::asio::spawn(m_context, [&](boost::asio::yield_context yield) {
        incomingHandshakeLoop(yield, m_connections.back());
    });
}

void ConnectionManager::incomingHandshakeLoop(boost::asio::yield_context yield, Connection& connection)
{
    boost::system::error_code ec;
    char buff[16];
    buff[0] = 0x49;
    connection.socket.async_send(boost::asio::buffer(buff, 1), yield[ec]);

    if (ec) {
        BOOST_LOG_FUNCTION();
        BOOST_LOG(m_logger) << "Send 1 failed: " << ec;
        dropConnection(connection);
        return;
    }

    connection.socket.async_receive(boost::asio::buffer(buff, 3), yield[ec]);

    if (ec) {
        BOOST_LOG_FUNCTION();
        BOOST_LOG(m_logger) << "Recv 3 failed: " << ec;
        dropConnection(connection);
        return;
    }

    if (std::equal(buff, buff + 3, "GET")) {
        // upload
    } else if (std::equal(buff, buff + 3, "SEN")) {
        // download
    } else {
        connection.socket.async_receive(boost::asio::buffer(buff + 3, 13), yield[ec]);

        if (ec) {
            BOOST_LOG_FUNCTION();
            BOOST_LOG(m_logger) << "Recv 13 failed: " << ec;
            dropConnection(connection);
            return;
        }

        switch (GetKeyBlockGenerator(buff)) {
        case BlockGeneratorId::PrimaryClient:
            // for (int i = 0; i < m_primary.peers.size(); i++) {
            //     if (m_primary.peers[i].state == PeerState::WaitingForIncomingConnection && m_primary.peers[i].node.equalsTcp(connection.endPoint())) {
            //         m_primary.onPeerConnect(i);
            //     }
            // }
            break;
        case BlockGeneratorId::SecondaryClient:
            // peer.handler = &m_secondaryClient;
            break;
        case BlockGeneratorId::ChatClient:
            // peer.handler = &m_chatClient;
            break;
        default:
            BOOST_LOG_FUNCTION();
            BOOST_LOG(m_logger) << "Unhandled block generator: " << ec;
            dropConnection(connection);
            return;
        }
    }

    // peer.state = PeerState::Joined;
    // connection.resetLastActivity();
    // EndPoint ep(peer.remoteEndPoint.address().to_v4().to_uint(), peer.remoteEndPoint.port());
    // peer.handler->handleConnect(peerIndex, ep);
}

void ConnectionManager::doChatConnection(boost::asio::yield_context yield, int chatClientIndex)
{
    auto& client = m_chatClients[chatClientIndex];
    boost::system::error_code ec;
    char buff[1000];

    m_connections.emplace_back(tcp::socket(m_context), tcp::endpoint(boost::asio::ip::address_v4(client.host.address()), client.host.port()));

    m_connections.back().socket.async_connect(m_connections.back().remoteEndPoint, yield[ec]);

    if (ec) {
        BOOST_LOG_FUNCTION();
        BOOST_LOG(m_logger) << "Connect failed: " << ec;
        m_connections.back().socket.close();
        return;
    }

    m_connections.back().socket.async_receive(boost::asio::buffer(buff, 1), yield[ec]);

    if (ec) {
        BOOST_LOG_FUNCTION();
        BOOST_LOG(m_logger) << "Recv 1 failed: " << ec;
        m_connections.back().socket.close();
        return;
    }
    if (buff[0] != 0x49) {
        BOOST_LOG_FUNCTION();
        BOOST_LOG(m_logger) << "Recv 1 byte is wrong: " << ec;
        m_connections.back().socket.close();
        return;
    }

    GenerateKeyBlock(buff, BlockGeneratorId::ChatClient);
    m_connections.back().socket.async_send(boost::asio::buffer(buff, 16), yield[ec]);

    if (ec) {
        BOOST_LOG_FUNCTION();
        BOOST_LOG(m_logger) << "Recv 1 failed: " << ec;
        m_connections.back().socket.close();
        return;
    }

    m_connections.back().socket.async_receive(boost::asio::buffer(buff, 16), yield[ec]);

    if (ec) {
        BOOST_LOG_FUNCTION();
        BOOST_LOG(m_logger) << "Recv 1 failed: " << ec;
        m_connections.back().socket.close();
        return;
    }

    StreamEncryption enc;
    if (!enc.parseServerKeys(buff, BlockGeneratorId::ChatServer)) {
        BOOST_LOG_FUNCTION();
        BOOST_LOG(m_logger) << "Wrong block id.";
        m_connections.back().socket.close();
        return;
    }

    m_chatClients[chatClientIndex].enc = enc;
    BinaryReader reader(buff, 1000);

    while (true) {
        m_connections.back().socket.async_receive(boost::asio::buffer(buff, 4), yield[ec]);
        enc.decrypt(buff, 4);
        reader.setBuffer(0, 4);
        reader.skip(2);
        wpn_short_t length = reader.readShort();

        if (length > 1000) {
            BOOST_LOG_FUNCTION();
            BOOST_LOG(m_logger) << "Message length too long.";
            m_connections.back().socket.close();
            return;
        }

        m_connections.back().socket.async_receive(boost::asio::buffer(buff + 4, length), yield[ec]);
        enc.decrypt(buff, length);
        reader.setBuffer(0, length + 4);
        m_chatClients[chatClientIndex].onServerMessage(reader);
    }
}

void ConnectionManager::tick(boost::system::error_code err)
{
    std::cout << "tick loop" << std::endl;

    for (auto& client : m_chatClients) {
        if (client.state == ChatPeerState::Disconnected) {
            client.state = ChatPeerState::Waiting;
            client.host = RoomName("Pandora!_0100007F1446").endPoint().value();
        } else if (client.state == ChatPeerState::Waiting) {
            // client.state = ChatPeerState::Connecting;
            // boost::asio::spawn(m_context, [&](boost::asio::yield_context yield) {
            //     doChatConnection(yield, 0);
            // });
        } else if (client.state == ChatPeerState::Connected) {
            // char sendBuff[10000];
            // BinaryWriter writer(sendBuff, 10000);
            // for (auto& msg : client.sendQueue) {
            //     msg->encode(writer);
            // }
            // client.enc.encrypt(sendBuff, writer.size());

            // boost::asio::spawn(m_context, [&](boost::asio::yield_context yc) {
            //     boost::system::error_code ec;
            //     m_connections.back().socket.async_send(boost::asio::buffer(sendBuff, writer.size()), yc[ec]);

            //     if (ec) {
            //         BOOST_LOG_FUNCTION();
            //         BOOST_LOG(m_logger) << "Send message failed: " << ec;
            //         m_connections.back().socket.close();
            //         return;
            //     }
            // });
        }
    }

    timer.expires_from_now(boost::posix_time::seconds(1));
    timer.async_wait([&](boost::system::error_code ec) {
        tick(ec);
    });
}

void ConnectionManager::receiveFromClientLoop(boost::asio::yield_context yield, int peerIndex, Connection& connection)
{
    // boost::system::error_code ec;
    // const int bufferSize = 1000;
    // char buff[bufferSize];
    // auto& peer = m_peers[peerIndex];

    // if (peer.state == PeerState::Accepted) {
    //     // need to determine which handler to use in the recieve loop
    //     // identification method 1: character sequence, 3 bytes
    //     // identification method 2: key block, 16 bytes
    //     buff[0] = 0x49;
    //     peer.socket.async_send(boost::asio::buffer(buff, 1), yield[ec]);

    //     if (ec) {
    //         BOOST_LOG_FUNCTION();
    //         BOOST_LOG(m_logger) << "Send 1 failed: " << ec;
    //         dropPeer(peer);
    //         return;
    //     }

    //     peer.socket.async_receive(boost::asio::buffer(buff, 3), yield[ec]);

    //     if (ec) {
    //         BOOST_LOG_FUNCTION();
    //         BOOST_LOG(m_logger) << "Recv 3 failed: " << ec;
    //         dropPeer(peer);
    //         return;
    //     }

    //     if (std::equal(buff, buff + 3, "GET")) {
    //         peer.handler = &m_upload;
    //     } else if (std::equal(buff, buff + 3, "SEN")) {
    //         peer.handler = &m_download;
    //     } else {
    //         peer.socket.async_receive(boost::asio::buffer(buff + 3, 13), yield[ec]);

    //         if (ec) {
    //             BOOST_LOG_FUNCTION();
    //             BOOST_LOG(m_logger) << "Recv 13 failed: " << ec;
    //             dropPeer(peer);
    //             return;
    //         }

    //         switch (GetKeyBlockGenerator(buff)) {
    //         case BlockGeneratorId::PrimaryClient:
    //             peer.handler = &m_primary;
    //             break;
    //         case BlockGeneratorId::SecondaryClient:
    //             peer.handler = &m_secondaryClient;
    //             break;
    //         case BlockGeneratorId::ChatClient:
    //             peer.handler = &m_chatClient;
    //             break;
    //         default:
    //             BOOST_LOG_FUNCTION();
    //             BOOST_LOG(m_logger) << "Unhandled block generator: " << ec;
    //             dropPeer(peer);
    //             return;
    //         }
    //     }

    //     peer.state = PeerState::Joined;
    //     peer.resetLastActivity();
    //     EndPoint ep(peer.remoteEndPoint.address().to_v4().to_uint(), peer.remoteEndPoint.port());
    //     peer.handler->handleConnect(peerIndex, ep);
    // } else if (peer.state == PeerState::Connecting) {
    //     peer.socket = tcp::socket(m_context);
    //     peer.socket.async_connect(peer.remoteEndPoint, yield[ec]);

    //     if (ec) {
    //         BOOST_LOG_FUNCTION();
    //         BOOST_LOG(m_logger) << "Connect failed: " << ec;
    //         dropPeer(peer);
    //         return;
    //     }

    //     peer.state = PeerState::Connected;

    //     peer.socket.async_receive(boost::asio::buffer(buff, 1), yield[ec]);

    //     if (ec) {
    //         BOOST_LOG_FUNCTION();
    //         BOOST_LOG(m_logger) << "Recv 1 failed: " << ec;
    //         dropPeer(peer);
    //         return;
    //     }
    //     if (buff[0] != 0x49) {
    //         BOOST_LOG_FUNCTION();
    //         BOOST_LOG(m_logger) << "Recv 1 byte is wrong: " << ec;
    //         dropPeer(peer);
    //         return;
    //     }

    //     if (std::is_same<decltype(*peer.handler), decltype(m_chatClient)>::value) {
    //         GenerateKeyBlock(buff, BlockGeneratorId::ChatClient);
    //     }
    //     else if (std::is_same<decltype(*peer.handler), decltype(m_chatClient)>::value) {

    //     }

    //     peer.socket.async_receive(boost::asio::buffer(buff, 3), yield[ec]);

    //     if (ec) {
    //         BOOST_LOG_FUNCTION();
    //         BOOST_LOG(m_logger) << "Recv 3 failed: " << ec;
    //         dropPeer(peer);
    //         return;
    //     }

    // }

    // // TODO: need to make a base class for handlers or template so the following code does not need
    // //       a reference to a specific type like SecondaryClientHandler. Need common functions like
    // //       handleConnect, handleData, etc. Also, exposing header size might be worthwhile since it
    // //       will simplify the defragmentation code I would need to write inside the handlers

    // // MessageHandler: headerSize, bodyLength(char*), handleMessage(char*)
    // // ...
    // // class ChatClientHandler : public MessageHandler<4, 2, 2>
    // // class PrimaryHandler : public MessageHandler<17, 16, 1>

    // for (;;) {
    //     auto headBuffer = boost::asio::buffer(buff, peer.handler->headerSize());
    //     auto bytesRead = peer.socket.async_receive(headBuffer, yield[ec]);

    //     if (ec) {
    //         BOOST_LOG_FUNCTION();
    //         BOOST_LOG(m_logger) << "Recieve header failed: " << ec;
    //         dropPeer(peer);
    //         return;
    //     }

    //     auto bodySize = peer.handler->bodySize(buff);

    //     if (peer.handler->headerSize() + bodySize > bufferSize) {
    //         BOOST_LOG_FUNCTION();
    //         BOOST_LOG(m_logger) << "Message too large.";
    //         dropPeer(peer);
    //         return;
    //     }

    //     auto bodyBuffer = boost::asio::buffer(buff, bodySize);
    //     bytesRead = peer.socket.async_receive(bodyBuffer, yield[ec]);

    //     peer.handler->handleMessage(peer.id, BinaryReader(buff, peer.handler->headerSize() + bodySize));
    // }
}

} // namespace OpenMX