#include "EndPoint.h"

#include <iostream>
#include <stdexcept>

namespace OpenMX {

EndPoint::EndPoint(uint32_t address, uint16_t port)
    : m_address(address)
    , m_port(port)
{
}

uint32_t EndPoint::address() const
{
    return m_address;
}

uint16_t EndPoint::port() const
{
    return m_port;
}

bool EndPoint::isEmpty() const
{
    return m_address == 0 && m_port == 0;
}

std::optional<EndPoint> EndPoint::tryParse(std::string& s)
{
    // determine if using hash or ip:port format
    auto colonIndex = s.rfind(':');
    
    if (colonIndex != std::string::npos) {
        // ip:port format (Ex: 127.0.0.1:6000) colonIndex=9, addrLen=9
        return tryParse(s.substr(0, colonIndex), s.substr(colonIndex + 1));
    }

    // hash format (Ex: 0100007F1A2B)
    if (s.size() < 12) {
        return std::nullopt;
    }

    try {
        auto addressHex = s.substr(0, 8);
        auto portHex = s.substr(8, 4);
        size_t addressSize;
        size_t portSize;
        auto address = std::stoul(addressHex, &addressSize, 16);
        auto port = std::stoul(portHex, &portSize, 16);
        std::cout << "aHex=" << addressHex << " aNum=" << address << " pHex=" << portHex << " pNum=" << port << "\n";
        std::cout << "aSize=" << addressSize << " pSize=" << portSize << std::endl;

        if (address > UINT32_MAX || port > UINT16_MAX || addressSize != 8 || portSize != 4) {
            return std::nullopt;
        }

        return EndPoint(address, port);
    } catch (const std::invalid_argument& e) {
        return std::nullopt;
    } catch (const std::out_of_range& e) {
        return std::nullopt;
    }
}

std::optional<EndPoint> EndPoint::tryParse(std::string& ip, std::string& port)
{
    // determine if using hash or ip:port format
    EndPoint result;

    try {
        auto dot1 = ip.find('.');
        auto dot2 = ip.find('.', dot1 + 1);
        auto dot3 = ip.find('.', dot2 + 1);

        if (dot1 == std::string::npos || dot2 == std::string::npos || dot3 == std::string::npos) {
            return std::nullopt;
        }

        auto address1 = ip.substr(0, dot1);
        auto address2 = ip.substr(dot1 + 1, dot2 - dot1 - 1);
        auto address3 = ip.substr(dot2 + 1, dot3 - dot2 - 1);
        auto address4 = ip.substr(dot3 + 1);
        size_t address1Size;
        size_t address2Size;
        size_t address3Size;
        size_t address4Size;
        auto address1Parsed = std::stoul(address1, &address1Size);
        auto address2Parsed = std::stoul(address2, &address2Size);
        auto address3Parsed = std::stoul(address3, &address3Size);
        auto address4Parsed = std::stoul(address4, &address4Size);

        if (address1Parsed > UINT8_MAX || address2Parsed > UINT8_MAX || address3Parsed > UINT8_MAX || address4Parsed > UINT8_MAX) {
            return std::nullopt;
        }
        if (address1Size != address1.size() || address2Size != address2.size() || address3Size != address3.size() || address4Size != address4.size()) {
            return std::nullopt;
        }

        result.m_address = 0;
        result.m_address |= address4Parsed << 24;
        result.m_address |= address3Parsed << 16;
        result.m_address |= address2Parsed << 8;
        result.m_address |= address1Parsed;
    } catch (const std::invalid_argument& e) {
        return std::nullopt;
    } catch (const std::out_of_range& e) {
        return std::nullopt;
    }

    try {
        size_t portSize;
        auto portStringParsed = std::stoul(port, &portSize);

        if (portStringParsed > UINT16_MAX || portSize != port.size()) {
            return std::nullopt;
        }

        result.m_port = (uint16_t)portStringParsed;
    } catch (const std::invalid_argument& e) {
        return std::nullopt;
    } catch (const std::out_of_range& e) {
        return std::nullopt;
    }

    return result;
}

bool EndPoint::operator==(const EndPoint& other) const
{
    return other.m_address == m_address && other.m_port == m_port;
}

} // namespace OpenMX