#pragma once

#include <cstdint>
#include <string>

namespace OpenMX {
namespace protocol {

    class Username {
    private:
        std::string m_name;
        uint32_t m_parentAddress;
        uint16_t m_parentUdpPort;

    protected:
        Username(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort);

    public:
        std::string getName() const;
        uint32_t getParentAddress() const;
        uint16_t getParentUdpPort() const;

        static bool tryParse(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort, Username* result);
    };

} // namespace protocol
} // namespace OpenMX