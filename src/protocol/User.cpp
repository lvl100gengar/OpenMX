#include "User.h"

namespace OpenMX {
namespace protocol {

    User::User(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort, uint16_t lineType, uint32_t sharedFiles)
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

    bool User::tryParse(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort, uint16_t lineType, uint32_t sharedFiles, User* result)
    {
        // TODO: perform validation
        *result = User(name, parentAddress, parentUdpPort, lineType, sharedFiles);
        return true;
    }

} // namespace protocol
} // namespace OpenMX