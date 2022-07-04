#pragma once

#include <string>

namespace OpenMX {
namespace protocol {

    class Channelname {
    private:
        std::string m_name;

    protected:
        Channelname(const std::string& name);

    public:
        std::string getName() const;

        static bool tryParse(const std::string& name, Channelname* result);
    };

} // namespace protocol
} // namespace OpenMX