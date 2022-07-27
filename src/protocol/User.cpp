#include "User.h"

namespace OpenMX {

User::User(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort, uint16_t lineType, uint32_t sharedFiles)
    : Username(name, parentAddress, parentUdpPort)
    , m_lineType(lineType)
    , m_sharedFiles(sharedFiles)
{
}

User::User(uint16_t lineType, uint32_t parentAddress, uint16_t parentUdpPort, uint32_t sharedFiles, const std::string& name)
    : Username(name, parentAddress, parentUdpPort)
    , m_lineType(lineType)
    , m_sharedFiles(sharedFiles)
{
}

uint16_t User::getLineType() const
{
    return m_lineType;
}

uint32_t User::getSharedFiles() const
{
    return m_sharedFiles;
}

} // namespace OpenMX