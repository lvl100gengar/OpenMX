#include "Username.h"

namespace OpenMX {

Username::Username(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort)
    : m_name(name)
    , m_parentAddress(parentAddress)
    , m_parentUdpPort(parentUdpPort)
{
}

std::string Username::name() const
{
    return m_name;
}

uint32_t Username::parentAddress() const
{
    return m_parentAddress;
}

uint16_t Username::parentUdpPort() const
{
    return m_parentUdpPort;
}

bool Username::isValidBaseName() const
{
    // 4 characters min (Ex: a123)
    // 41 characters max (Ex: wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww452)
    if (m_name.size() < 4 || m_name.size() > 41)
        return false;

    // cannot contain spaces
    for (size_t i = 0; i < m_name.size() - 3; i++) {
        if (m_name.at(i) == ' ')
            return false;
    }

    // last 3 characters must be numbers 0-9
    for (size_t i = m_name.size() - 3; i < m_name.size(); i++) {
        if (m_name.at(i) < '0' || m_name.at(i) > '9')
            return false;
    }

    return true;
}

bool Username::isValidFullName() const
{
    return Username::isValidFullName(m_name);
}

bool Username::isReachable() const
{
    return isValidFullName() && m_parentAddress != 0 && m_parentUdpPort != 0;
}

bool Username::isValidFullName(const std::string& name)
{
    // 10 characters min (Ex: a123_12345)
    // 47 characters max (Ex: wwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwwww452_12345)
    if (name.size() < 10 || name.size() > 47)
        return false;

    // cannot contain spaces
    for (size_t i = 0; i < name.size() - 9; i++) {
        if (name.at(i) == ' ')
            return false;
    }

    // last 3 characters before underscore must be numbers 0-9
    for (size_t i = name.size() - 9; i < name.size() - 7; i++) {
        if (name.at(i) < '0' || name.at(i) > '9')
            return false;
    }

    if (name.at(name.size() - 6) != '_')
        return false;

    // last 5 characters must be numbers 0-9
    for (size_t i = name.size() - 5; i < name.size(); i++) {
        if (name.at(i) < '0' || name.at(i) > '9')
            return false;
    }

    return true;
}

void Username::toBytes(BinaryWriter& writer) const
{
    writer.writeString(m_name, true);
    writer.writeInt(m_parentAddress);
    writer.writeShort(m_parentUdpPort);
}

void Username::fromBytes(BinaryReader& reader)
{
    m_name = reader.readString();
    m_parentAddress = reader.readInt();
    m_parentUdpPort = reader.readShort();
}

} // namespace OpenMX