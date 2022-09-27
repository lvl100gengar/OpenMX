#include "User.h"
#include <sstream>

namespace OpenMX {

User::User(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort, uint16_t lineType, uint32_t sharedFiles, uint8_t rank)
    : Username(name, parentAddress, parentUdpPort)
    , m_lineType(lineType)
    , m_sharedFiles(sharedFiles)
    , m_rank(rank)
{
}

User::User(uint16_t lineType, uint32_t parentAddress, uint16_t parentUdpPort, uint32_t sharedFiles, const std::string& name)
    : Username(name, parentAddress, parentUdpPort)
    , m_lineType(lineType)
    , m_sharedFiles(sharedFiles)
{
}

uint16_t User::lineType() const
{
    return m_lineType;
}

uint32_t User::sharedFiles() const
{
    return m_sharedFiles;
}

void User::toBytesListOrder(BinaryWriter& writer, bool includeRank) const
{
    writer.writeString(m_name, true);
    writer.writeInt(m_parentAddress);
    writer.writeShort(m_parentUdpPort);
    writer.writeShort(m_lineType);
    writer.writeInt(m_sharedFiles);

    if (includeRank){
        writer.writeByte(m_rank);
    }
}

void User::fromBytesListOrder(BinaryReader& reader, bool includeRank)
{
    m_name = reader.readString();
    m_parentAddress = reader.readInt();
    m_parentUdpPort = reader.readShort();
    m_lineType = reader.readShort();
    m_sharedFiles = reader.readInt();
    m_rank = includeRank ? reader.readByte() : UserRank::NotProvided;
}

void User::toBytesLoginOrder(BinaryWriter& writer) const
{
    writer.writeShort(m_lineType);
    writer.writeInt(m_parentAddress);
    writer.writeShort(m_parentUdpPort);
    writer.writeInt(m_sharedFiles);
    writer.writeString(m_name, true);
}

void User::fromBytesLoginOrder(BinaryReader& reader)
{
    m_lineType = reader.readShort();
    m_parentAddress = reader.readInt();
    m_parentUdpPort = reader.readShort();
    m_sharedFiles = reader.readInt();
    m_name = reader.readString();
}

std::string User::describe() const
{
    std::ostringstream ss;
    ss << '[' << m_name << ']';
    return ss.str();
}

} // namespace OpenMX