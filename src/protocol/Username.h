#pragma once

#include "../io/BinaryWriter.h"
#include "../io/BinaryReader.h"

#include <cstdint>
#include <string>

namespace OpenMX {

class Username {
protected:
    std::string m_name;
    uint32_t m_parentAddress;
    uint16_t m_parentUdpPort;

public:
    Username() = default;
    Username(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort);

    std::string name() const;
    uint32_t parentAddress() const;
    uint16_t parentUdpPort() const;

    bool isValidBaseName() const;
    bool isValidFullName() const;
    bool isReachable() const;

    static bool isValidFullName(const std::string& name);

    void toBytes(BinaryWriter& writer) const;
    void fromBytes(BinaryReader& reader);
};

} // namespace OpenMX