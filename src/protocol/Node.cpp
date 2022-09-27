#include "Node.h"

#include "EndPoint.h"

namespace OpenMX {

Node::Node(uint32_t address, uint16_t udpPort, uint16_t tcpPort, uint8_t openPrimary, uint8_t openSecondary)
    : m_address(address)
    , m_udpPort(udpPort)
    , m_tcpPort(tcpPort)
    , m_openPrimary(openPrimary)
    , m_openSecondary(openSecondary)
{
}

uint32_t Node::address() const
{
    return m_address;
}

uint16_t Node::udpPort() const
{
    return m_udpPort;
}

uint16_t Node::tcpPort() const
{
    return m_tcpPort;
}

uint8_t Node::openPrimary() const
{
    return m_openPrimary;
}

uint8_t Node::openSecondary() const
{
    return m_openSecondary;
}

bool Node::equalsTcp(const EndPoint& ep) const {
    return address() == ep.address() && tcpPort() == ep.port();
}

bool Node::equalsUdp(const EndPoint& ep) const {
    return address() == ep.address() && udpPort() == ep.port();
}

} // namespace OpenMX