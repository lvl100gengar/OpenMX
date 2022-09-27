#pragma once

#include "../io/BinaryWriter.h"
#include "WpnTypes.h"
#include <string>
#include <sstream>

namespace OpenMX {

struct Message {
    void secondaryHeader(BinaryWriter& writer, wpn_short_t type, wpn_short_t length) const
    {
        writer.writeShort(type);
        writer.writeShort(length);
    }

    virtual void encode(BinaryWriter& writer) const = 0;
    // virtual void decode(BinaryReader& reader) = 0;
    virtual void describe(std::ostringstream& ss) const = 0;

    virtual std::string describe()
    {
        std::ostringstream ss;
        describe(ss);
        return ss.str();
    }
};

} // namespace OpenMX