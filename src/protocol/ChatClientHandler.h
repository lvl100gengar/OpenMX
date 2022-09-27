#pragma once

#include "../io/BinaryReader.h"
#include "EndPoint.h"
#include "Message.h"
#include "Encryption.h"
#include <memory>
#include <vector>

namespace OpenMX {

enum class ChatPeerState : char {
    Disconnected,
    Waiting,
    Connecting,
    Connected
};

class ChatClientHandler {
public:
public:
    EndPoint host;
    std::vector<std::unique_ptr<Message>> sendQueue;
    ChatPeerState state;
    StreamEncryption enc;

    ChatClientHandler() = default;

    void onServerMessage(BinaryReader message);

    void onServerConnect();
    void onServerDisconnect();

    void tick();
};

} // namespace OpenMX