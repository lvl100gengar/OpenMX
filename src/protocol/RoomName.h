#pragma once

#include "../io/BinaryReader.h"
#include "../io/BinaryWriter.h"
#include "EndPoint.h"
#include <string>
#include <optional>

namespace OpenMX {

class RoomName {
public:
    RoomName() = default;
    RoomName(const std::string& name);

    std::string name() const;
    std::optional<EndPoint> endPoint() const;

    bool isValid() const;

    void toBytes(BinaryWriter& writer) const;
    void fromBytes(BinaryReader& reader);
    
    std::string describe() const;

private:
    std::string m_name;
};

} // namespace OpenMX