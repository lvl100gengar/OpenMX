#pragma once

#include <cstdint>

namespace OpenMX {

class EndPoint;

class Node {
private:
    uint32_t m_address;
    uint16_t m_udpPort;
    uint16_t m_tcpPort;
    uint8_t m_openPrimary;
    uint8_t m_openSecondary;

public:
    Node() = default;
    Node(uint32_t address, uint16_t udpPort, uint16_t tcpPort, uint8_t openPrimary, uint8_t openSecondary);

    uint32_t address() const;
    uint16_t udpPort() const;
    uint16_t tcpPort() const;
    uint8_t openPrimary() const;
    uint8_t openSecondary() const;

    bool equalsTcp(const EndPoint& ep) const;
    bool equalsUdp(const EndPoint& ep) const;
};

} // namespace OpenMX