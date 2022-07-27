#include <stdexcept>

#include "Channelname.h"

namespace OpenMX {

    Channelname::Channelname(const std::string& name)
        : m_name(name)
    {
    }

    std::string Channelname::getName() const
    {
        return m_name;
    }

    bool Channelname::isValid() const
    {
        // name and hash seperated by underscore
        auto underscoreIndex = m_name.rfind('_');

        return true;
    }

} // namespace OpenMX