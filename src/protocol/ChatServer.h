#pragma once

#include "ChatServerSettings.h"
#include "../io/BinaryReader.h"
#include "../io/BinaryWriter.h"
#include "MessageHandler.h"
#include "ChatMessages.h"

#include <vector>
#include <mutex>

namespace OpenMX {

struct ClientData
{
    // status flags
    bool inUse;
    bool isJoined;
    
    // user info
    std::string channel;
    std::string name;
    uint32_t sharedFiles;
    uint16_t lineType;
    uint32_t parentAddress;
    uint16_t parentPort;
    uint8_t rank;

    std::string softwareName;
    std::string softwareVersion;

EndPoint endPoint;

    std::string textFormat;
    std::string permissions;
    bool enableWinmx353;

    std::vector<Message> sendQueue;
};


class ChatServer : public MessageHandler {
private:
    ChatServerSettings m_settings;

    std::vector<ClientData> m_clients;
    std::mutex m_clientLock;

    int findClient(const std::string& name);
    void sendTextToAll(std::string format, std::string text, const std::string requiredPermissions);
    void sendTextToAll(int sourceConnectionId, std::string text, const std::string requiredPermissions);
    void sendJoinToAll(int sourceConnectionId);
    void sendPartToAll(int sourceConnectionId);
    void sendRenameToAll(int sourceConnectionId, const std::string& newName, uint32_t newParentAddress, uint16_t newParentPort);
    std::string formatText(std::string format, int connectionId, std::string text);
    std::string formatUser(std::string format, int connectionId, bool color);
    std::string formatRename(std::string format, int connectionId, std::string oldName, uint32_t oldParentAddress, uint16_t oldParentPort);

public:
    ChatServer();
    ~ChatServer();

    virtual int handleConnect(const EndPoint& remoteEndPoint) override;
    virtual void handleDisconnect(int connectionId) override;
    virtual void handleMessage(int connectionId, int messageId, BinaryReader message) override;
    virtual void tick() override;
};

}