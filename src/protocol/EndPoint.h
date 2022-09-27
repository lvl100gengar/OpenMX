#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace OpenMX {

class EndPoint {
private:
    uint32_t m_address { 0 };
    uint16_t m_port { 0 };

public:
    EndPoint() = default;
    EndPoint(uint32_t address, uint16_t port);

    uint32_t address() const;
    uint16_t port() const;
    bool isEmpty() const;

    static std::optional<EndPoint> tryParse(std::string& s);
    static std::optional<EndPoint> tryParse(std::string& ip, std::string& port);

    bool operator==(const EndPoint& other) const;
};

} // namespace OpenMX