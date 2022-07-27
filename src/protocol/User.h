#include "../io/BinaryReader.h"
#include "Username.h"

namespace OpenMX {

class User : public Username {

private:
    uint16_t m_lineType;
    uint32_t m_sharedFiles;

public:
    User() = default;
    User(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort, uint16_t lineType, uint32_t sharedFiles);
    User(uint16_t lineType, uint32_t parentAddress, uint16_t parentUdpPort, uint32_t sharedFiles, const std::string& name);

    uint16_t getLineType() const;
    uint32_t getSharedFiles() const;
};

} // namespace OpenMX