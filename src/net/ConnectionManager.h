#pragma once

#include "../protocol/ChatClientHandler.h"
#include "../net/Connection.h"

#include <boost/asio.hpp>
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/log/sources/logger.hpp>
#include <thread>

namespace OpenMX {

class PrimaryHandler;
class SecondaryHandler;

class ConnectionManager {
public:
    ConnectionManager();
    using tcp = boost::asio::ip::tcp;
    void handleIncoming(tcp::socket&& socket, tcp::endpoint& remoteEndPoint);
    void tick(boost::system::error_code ec);

private:
    boost::log::sources::logger m_logger;
    boost::asio::io_context m_context;
    boost::posix_time::seconds interval = boost::posix_time::seconds(1);  // 1 second
    boost::asio::deadline_timer timer = boost::asio::deadline_timer(m_context, interval);

    PrimaryHandler& m_primary;
    SecondaryHandler& m_secondary;
    std::vector<Connection> m_connections;
    std::vector<ChatClientHandler> m_chatClients;
    std::thread* m_mainThread;

    void dropConnection(Connection& connection);

    void doChatConnection(boost::asio::yield_context yc, int chatClientIndex);

    void incomingHandshakeLoop(boost::asio::yield_context yc, Connection& connection);
    void receiveFromPeerLoop(boost::asio::yield_context yc, int peerIndex, Connection& connection);
    void receiveFromClientLoop(boost::asio::yield_context yc, int peerIndex, Connection& connection);
    void receiveFromServerLoop(boost::asio::yield_context yc, Connection& connection);
};

} // namespace OpenMX