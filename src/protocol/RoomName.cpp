#include "RoomName.h"
#include <sstream>
#include <stdexcept>

namespace OpenMX {

RoomName::RoomName(const std::string& name)
    : m_name(name)
{
}

std::string RoomName::name() const
{
    return m_name;
}

std::optional<EndPoint> RoomName::endPoint() const {
    size_t underscoreIndex = m_name.rfind('_');

    if (underscoreIndex == std::string::npos || underscoreIndex == m_name.size() - 1) {
        return std::nullopt;
    }

    return EndPoint::tryParse(m_name.substr(underscoreIndex + 1));
}

bool RoomName::isValid() const
{
    // name and hash seperated by underscore
    auto underscoreIndex = m_name.rfind('_');

    if (underscoreIndex == std::string::npos || underscoreIndex == 0 || underscoreIndex == m_name.size() - 1) {
        return false;
    }

    return EndPoint::tryParse(m_name.substr(underscoreIndex + 1)).has_value();
}

void RoomName::toBytes(BinaryWriter& writer) const
{
    writer.writeString(m_name, true);
}

void RoomName::fromBytes(BinaryReader& reader)
{
    m_name = reader.readString();
}

std::string RoomName::describe() const
{
    std::ostringstream ss;
    ss << '[' << m_name << ']';
    return ss.str();
}

} // namespace OpenMX