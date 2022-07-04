#include "Username.h"

namespace OpenMX {
namespace protocol {

    Username::Username(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort)
        : m_name(name)
        , m_parentAddress(parentAddress)
        , m_parentUdpPort(parentUdpPort)
    {
    }

    std::string Username::getName() const
    {
        return m_name;
    }

    uint32_t Username::getParentAddress() const
    {
        return m_parentAddress;
    }

    uint16_t Username::getParentUdpPort() const
    {
        return m_parentUdpPort;
    }

    bool Username::tryParse(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort, Username* result)
    {
        // TODO: perform validation
        *result = Username(name, parentAddress, parentUdpPort);
        return true;
    }

} // namespace protocol
} // namespace OpenMX