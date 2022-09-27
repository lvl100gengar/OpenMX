#pragma once

#include "../io/BinaryReader.h"
#include "../io/BinaryWriter.h"
#include "Username.h"

namespace OpenMX {

enum UserRank : uint8_t {
    Default = 0,
    Admin = 1,
    Moderator = 2,
    NotProvided = 255
};

class User : public Username {
public:
    User() = default;
    User(const std::string& name, uint32_t parentAddress, uint16_t parentUdpPort, uint16_t lineType, uint32_t sharedFiles, uint8_t rank = UserRank::NotProvided);
    User(uint16_t lineType, uint32_t parentAddress, uint16_t parentUdpPort, uint32_t sharedFiles, const std::string& name);

    uint16_t lineType() const;
    uint32_t sharedFiles() const;
    uint8_t rank() const;

    void toBytesListOrder(BinaryWriter& writer, bool includeRank) const;
    void fromBytesListOrder(BinaryReader& reader, bool includeRank);

    void toBytesLoginOrder(BinaryWriter& writer) const;
    void fromBytesLoginOrder(BinaryReader& reader);
    
    std::string describe() const;

private:
    uint16_t m_lineType;
    uint32_t m_sharedFiles;
    uint8_t m_rank;
};

} // namespace OpenMX