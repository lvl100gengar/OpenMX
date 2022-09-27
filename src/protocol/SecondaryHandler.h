#pragma once

#include "../io/BinaryReader.h"
#include "Node.h"
#include "Message.h"

namespace OpenMX {

class SecondaryHandler {
public:
    std::vector<Node> nodes;
    Node host;
    std::vector<Message> sendQueue;
    
    SecondaryHandler() = default;

    void onServerMessage(BinaryReader message);

    void onServerConnect();
    void onServerDisconnect();

    void tick();
};

} // namespace OpenMX