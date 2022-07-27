#pragma once

#include <cstdint>
#include <string>

namespace OpenMX {

class Username {
private:
    std::string m_name;
    uint32_t m_parentAddress;
    uint16_t m_parentUdpPort;

public:
    Username() = default;
    Username(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort);

    std::string getName() const;
    uint32_t getParentAddress() const;
    uint16_t getParentUdpPort() const;

    bool isValidBaseName() const;
    bool isValidFullName() const;
    bool isReachable() const;

    static bool isValidFullName(const std::string& name);
};

} // namespace OpenMX