#include "Channelname.h"

namespace OpenMX {
namespace protocol {

    Channelname::Channelname(const std::string& name)
        : m_name(name)
    {
    }

    std::string Channelname::getName() const
    {
        return m_name;
    }

    bool Channelname::tryParse(const std::string& name, Channelname* result)
    {
        // TODO: actually vet the string
        *result = Channelname(name);
        return true;
    }

} // namespace protocol
} // namespace OpenMX