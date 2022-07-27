#pragma once

#include <cstdint>

namespace OpenMX {

class Node {
private:
    uint32_t m_address;
    uint16_t m_udpPort;
    uint16_t m_tcpPort;
    uint8_t m_openPrimary;
    uint8_t m_openSecondary;

public:
    Node(uint32_t address, uint16_t udpPort, uint16_t tcpPort, uint8_t openPrimary, uint8_t openSecondary);

    uint32_t getAddress() const;
    uint16_t getUdpPort() const;
    uint16_t getTcpPort() const;
    uint8_t getOpenPrimary() const;
    uint8_t getOpenSecondary() const;
};

} // namespace OpenMX