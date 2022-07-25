#include "EndPoint.h"

#include <stdexcept>

namespace OpenMX {
namespace net {

    EndPoint::EndPoint(uint32_t address, uint16_t port)
        : m_address(address)
        , m_port(port)
    {
    }

    bool EndPoint::isEmpty() const
    {
        return m_address == 0 && m_port == 0;
    }

    bool EndPoint::tryParse(std::string& s, EndPoint& result)
    {
        // determine if using hash or ip:port format
        auto colonIndex = s.find(':');

        if (colonIndex == -1) {
            // hash format (Ex: 0100007F1A2B)
            if (s.size() != 12) {
                return false;
            }

            try {
                auto addressHex = s.substr(0, 8);
                auto portHex = s.substr(8, 4);
                auto address = std::stoul(addressHex, nullptr, 8);
                auto port = std::stoul(portHex, nullptr, 8);

                if (address > UINT32_MAX || port > UINT16_MAX) {
                    return false;
                }

                result.m_address = address;
                result.m_port = port;
            } catch (const std::invalid_argument& e) {
                return false;
            } catch (const std::out_of_range& e) {
                return false;
            }
        } else {
            // ip:port format (Ex: 127.0.0.1:6000) colonIndex=9, addrLen=9
            try {
                auto dot1 = s.find('.');
                auto dot2 = s.find('.', dot1 + 1);
                auto dot3 = s.find('.', dot2 + 1);

                if (dot1 == -1 || dot2 == -1 || dot3 == -1 || dot1 > colonIndex || dot2 > colonIndex || dot3 > colonIndex) {
                    return false;
                }

                auto address1 = s.substr(0, dot1);
                auto address2 = s.substr(dot1 + 1, dot2 - dot1 - 1);
                auto address3 = s.substr(dot2 + 1, dot3 - dot2 - 1);
                auto address4 = s.substr(dot3 + 1, colonIndex - dot3 - 1);
                auto address1Parsed = std::stoul(address1);
                auto address2Parsed = std::stoul(address2);
                auto address3Parsed = std::stoul(address3);
                auto address4Parsed = std::stoul(address4);

                if (address1Parsed > UINT8_MAX || address2Parsed > UINT8_MAX || address3Parsed > UINT8_MAX || address4Parsed > UINT8_MAX) {
                    return false;
                }

                result.m_address = 0;
                result.m_address |= address1Parsed << 24;
                result.m_address |= address2Parsed << 16;
                result.m_address |= address3Parsed << 8;
                result.m_address |= address4Parsed;
            } catch (const std::invalid_argument& e) {
                return false;
            } catch (const std::out_of_range& e) {
                return false;
            }

            try {
                auto portString = s.substr(colonIndex + 1);
                auto portStringParsed = std::stoul(portString);

                if (portStringParsed > UINT16_MAX) {
                    return false;
                }

                result.m_port = (uint16_t)portStringParsed;
            } catch (const std::invalid_argument& e) {
                return false;
            } catch (const std::out_of_range& e) {
                return false;
            }
        }

        return true;
    }

    bool EndPoint::operator==(const EndPoint& other) const {
        return other.m_address == m_address && other.m_port == m_port;
    }

} // namespace net
} // namespace OpenMX