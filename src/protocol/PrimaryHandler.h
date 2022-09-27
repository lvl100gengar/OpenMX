#pragma once

#include "../io/BinaryReader.h"
#include "EndPoint.h"
#include "Node.h"
#include "Message.h"
#include "WpnTypes.h"
#include <vector>

namespace OpenMX {

enum class PeerState : char {
    Unused,
    // A node was set in a UDP exchange and we are waiting for the TCP connection
    WaitingForIncomingConnection,
    // The peer was dropped internally and the ConnectionManager should now close the connection
    Dropped,
    // 
    Connected
};

class PrimaryHandler {
public:
    struct Peer {
        Node node;
        PeerState state;
        std::vector<Message> sendQueue;
    };
    struct HostedSecondary {
        EndPoint endPoint;
        std::vector<Message> sendQueue;
    };

    PrimaryHandler() = default;

    wpn_byte_t openPrimaries() const;
    wpn_byte_t openSecondaries() const;
    
    std::vector<Node> nodes;
    std::vector<Peer> peers;
    std::vector<HostedSecondary> clients;

    void onUdpMessage(wpn_int_t remoteAddress, wpn_short_t remotePort, BinaryReader message);
    void onPeerMessage(int index, BinaryReader message);
    void onClientMessage(int index, BinaryReader message);

    // TCP Connections
    // Outgoing connections made when openPrimary/openSecondary are not zero using endpoint from nodes
    // All connections are passed here after key exchange

    void onPeerConnect(int index);
    int onClientConnect(int index);

    // 
    // 

    void onPeerDisconnect(int index);
    void onClientDisconnect(int index);

    void tick();

private:

};

} // namespace OpenMX