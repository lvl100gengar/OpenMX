#pragma once

#include <cstdint>
#include <string>

namespace OpenMX {
namespace net {

    class EndPoint {
    private:
        uint32_t m_address;
        uint16_t m_port;
    public:
        EndPoint() = default;
        EndPoint(uint32_t address, uint16_t port);

        uint32_t address() const;
        uint16_t port() const;
        bool isEmpty() const;

        static bool tryParse(std::string& s, EndPoint& result);
        static bool tryParse(std::string& ip, std::string& port, EndPoint& result);

         bool operator==(const EndPoint& other) const;
    };

} // namespace net
} // namespace OpenMX