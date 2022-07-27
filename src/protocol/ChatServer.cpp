#include "ChatServer.h"
#include "Channelname.h"
#include "ChatMessages.h"
#include "User.h"
#include "Username.h"

namespace OpenMX {

int ChatServer::handleConnect(const EndPoint& remoteEndPoint)
{
    int connectionsFromAddress;
    int connectionsTotal;
    int newConnectionId = -1;

    if (m_settings.isBanned(remoteEndPoint.address())) {
        return -1;
    }

    m_clientLock.lock();

    for (auto&& c : m_clients) {
        if (!c.inUse) {
            if (newConnectionId = -1) {
                newConnectionId = connectionsTotal;
            }
            continue;
        }

        ++connectionsTotal;

        if (c.endPoint.address() == remoteEndPoint.address()) {
            ++connectionsFromAddress;
        }
    }

    if (connectionsTotal >= m_settings.maxConnections() || connectionsFromAddress >= m_settings.maxConnectionsPerAddress()) {
        m_clientLock.unlock();
        return -1;
    }

    if (newConnectionId == -1) {
        m_clients.emplace_back();
        newConnectionId = connectionsTotal;
    }

    m_clients[newConnectionId].inUse = true;
    m_clients[newConnectionId].endPoint = remoteEndPoint;

    m_clientLock.unlock();

    return newConnectionId;
}

void ChatServer::handleDisconnect(int connectionId)
{
    m_clientLock.lock();
    m_clients[connectionId].inUse = false;
    m_clients[connectionId].isJoined = false;
    m_clientLock.unlock();
}

void ChatServer::handleMessage(int connectionId, int messageId, BinaryReader msg)
{
    switch (messageId) {
    case ChatLogin::type: {
        ChatLogin login(msg);

        if (!Username::isValidFullName(login.userName)) {
            sendTextToAll(m_settings.messageFormat("INVALID_USERNAME"), login.userName, "+");
            m_manager.DropConnection(*this, connectionId);
            return;
        }
        if (findClient(login.userName)) {
            sendTextToAll(m_settings.messageFormat("DUPLICATE_USERNAME"), login.userName, "+");
            m_manager.DropConnection(*this, connectionId);
            return;
        }
        if (m_settings.containedBlockedName(login.userName)) {
            sendTextToAll(m_settings.messageFormat("BLOCKED_USERNAME"), login.userName, "+");
            m_manager.DropConnection(*this, connectionId);
            return;
        }

        m_clients[connectionId].channel = login.roomName;
        m_clients[connectionId].name = login.userName;
        m_clients[connectionId].parentAddress = login.parentAddress;
        m_clients[connectionId].parentPort = login.parentUdpPort;
        m_clients[connectionId].lineType = login.lineType;
        m_clients[connectionId].sharedFiles = login.sharedFiles;
        m_clients[connectionId].isJoined = true;

        sendJoinToAll(connectionId);
        break;
    }
    case ChatRename::type: {
        ChatRename rename(msg);

        if (!Username::isValidFullName(rename.userName)) {
            sendTextToAll(m_settings.messageFormat("INVALID_USERNAME"), rename.userName, "+");
            m_manager.DropConnection(*this, connectionId);
            return;
        }
        if (findClient(rename.userName)) {
            sendTextToAll(m_settings.messageFormat("DUPLICATE_USERNAME"), rename.userName, "+");
            m_manager.DropConnection(*this, connectionId);
            return;
        }
        if (m_settings.containedBlockedName(rename.userName)) {
            sendTextToAll(m_settings.messageFormat("BLOCKED_USERNAME"), rename.userName, "+");
            m_manager.DropConnection(*this, connectionId);
            return;
        }

        sendRenameToAll(connectionId, rename.userName, rename.parentAddress, rename.parentUdpPort);

        m_clients[connectionId].name = rename.userName;
        m_clients[connectionId].parentAddress = rename.parentAddress;
        m_clients[connectionId].parentPort = rename.parentUdpPort;
        m_clients[connectionId].lineType = rename.lineType;
        m_clients[connectionId].sharedFiles = rename.sharedFiles;
        break;
    }
    case ChatClientText::type: {
        ChatClientText text(msg);
        sendTextToAll(connectionId, text.text, "");
        break;
    }
    case ChatClientAction::type: {
        ChatClientAction action(msg);
        sendTextToAll(connectionId, "/action " + action.text, "");
        break;
    }
    case ChatClient353Support::type: {
        // no payload

        break;
    }
    case ChatClientRedirect::type: {
        ChatClientRedirect redirect(msg);
        break;
    }
    case ChatClientColorText::type: {
        ChatClientColorText text(msg);
        sendTextToAll(connectionId, text.text, "");
        break;
    }
    case WcsClientIpSendSupport::type: {
        // no payload

        break;
    }
    case WcsSoftwareName::type: {
        WcsSoftwareName software(msg);

        if (m_settings.containedBlockedWord(software.name) || m_settings.containedBlockedWord(software.version)) {
            return;
        }

        m_clients[connectionId].softwareName = software.name;
        m_clients[connectionId].softwareVersion = software.version;
        break;
    }
    case ChatKeepAlive::type: {
        // no payload

        break;
    }
    default: {
        // unknown message type
        char buffer[100];
        std::snprintf(buffer, 100, "Unhandled message: type=%x length=%u", messageId, msg.capacity());
        sendTextToAll("", buffer, false);
        break;
    }
    }
}

void ChatServer::tick()
{
}

int ChatServer::findClient(const std::string& name)
{
    for (size_t i = 0; i < m_clients.size(); i++) {
        if (m_clients[i].name == name) {
            return i;
        }
    }

    return -1;
}

void ChatServer::sendJoinToAll(int sourceConnectionId)
{
    // Normal
    // Normal w/ rank
    // Normal w/ IP
    // Fancy
    // Fancy w/ IP

    ClientData& newClient = m_clients[sourceConnectionId];

    for (auto&& client : m_clients) {
        if (!client.isJoined)
            continue;

        if (m_settings.fancyEntry()) {
            if (client.enableWinmx353) {
                // Fancy entry with color and rank
                ChatServerColorText fancyEntry;

                if (client.permissions.find_first_of("I*!") == std::string::npos) {
                    fancyEntry.text = formatUser(m_settings.messageFormat("FANCY_ENTRY_IP"), sourceConnectionId, true);
                } else {
                    fancyEntry.text = formatUser(m_settings.messageFormat("FANCY_ENTRY"), sourceConnectionId, true);
                }

                client.sendQueue.push_back(ChatUserListRank(newClient));
                client.sendQueue.push_back(std::move(fancyEntry));
            } else {
                // Fancy entry without color and rank
                ChatServerText fancyEntry;

                if (client.permissions.find_first_of("I*!") == std::string::npos) {
                    fancyEntry.text = formatUser(m_settings.messageFormat("FANCY_ENTRY_IP"), sourceConnectionId, false);
                } else {
                    fancyEntry.text = formatUser(m_settings.messageFormat("FANCY_ENTRY"), sourceConnectionId, false);
                }

                client.sendQueue.push_back(ChatUserList(newClient));
                client.sendQueue.push_back(std::move(fancyEntry));
            }
        } else {
            // Standard entry
            bool enable353 = client.enableWinmx353;
            bool enableIp = client.permissions.find_first_of("I*!") != std::string::npos;

            if (enableIp) {
                client.sendQueue.push_back(ChatUserJoinRankIp(newClient));
            } else if (enable353) {
                client.sendQueue.push_back(ChatUserJoinRank(newClient));
            } else {
                client.sendQueue.push_back(ChatUserJoin(newClient));
            }
        }
    }
}

void ChatServer::sendTextToAll(std::string format, std::string text, const std::string requiredPermissions)
{
    // Used for sending text that did not come from a user
    // text in this case represents any text argument to format

    // Variations on sent text:
    // Color | Plain

    for (auto&& client : m_clients) {
        if (!client.isJoined)
            continue;

        bool hasPermissions = true;

        for (auto&& perm : requiredPermissions) {
            if (client.permissions.find(perm) == std::string::npos) {
                hasPermissions = false;
                break;
            }
        }

        if (!hasPermissions)
            continue;

        if (client.enableWinmx353 && client.permissions.find('b') == std::string::npos) {
            // color message
            ChatServerColorText text;
            text.text = format;
            client.sendQueue.push_back(text);
        } else {
            // message without color
            ChatServerText text;
            text.text = format;
            client.sendQueue.push_back(text);
        }
    }
}

}