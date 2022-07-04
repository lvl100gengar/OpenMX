#include "Username.h"

namespace OpenMX {
namespace protocol {

    class User : public Username {

    private:
        uint16_t m_lineType;
        uint32_t m_sharedFiles;

    protected:
        User(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort, uint16_t lineType, uint32_t sharedFiles);

    public:
        uint16_t getLineType() const;
        uint32_t getSharedFiles() const;

        static bool tryParse(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort, uint16_t lineType, uint32_t sharedFiles, User* result);

    };

} // namespace protocol
} // namespace OpenMX