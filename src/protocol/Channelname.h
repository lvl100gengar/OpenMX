#pragma once

#include "../net/EndPoint.h"
#include <string>

namespace OpenMX {

class Channelname {
private:
    std::string m_name;

public:
    Channelname(const std::string& name);

    std::string getName() const;
    EndPoint getEndPoint() const;

    bool isValid() const;
};

} // namespace OpenMX