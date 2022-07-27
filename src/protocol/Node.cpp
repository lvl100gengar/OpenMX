#include "Node.h"

namespace OpenMX {

Node::Node(uint32_t address, uint16_t udpPort, uint16_t tcpPort, uint8_t openPrimary, uint8_t openSecondary)
    : m_address(address)
    , m_udpPort(udpPort)
    , m_tcpPort(tcpPort)
    , m_openPrimary(openPrimary)
    , m_openSecondary(openSecondary)
{
}

uint32_t Node::getAddress() const
{
    return m_address;
}

uint16_t Node::getUdpPort() const
{
    return m_udpPort;
}

uint16_t Node::getTcpPort() const
{
    return m_tcpPort;
}

uint8_t Node::getOpenPrimary() const
{
    return m_openPrimary;
}

uint8_t Node::getOpenSecondary() const
{
    return m_openSecondary;
}

} // namespace OpenMX