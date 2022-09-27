#include "protocol/EndPoint.h"

#include "../catch.hpp"

#include <string>

TEST_CASE("Construct default")
{
    uint32_t address = 0;
    uint16_t port = 0;
    OpenMX::EndPoint ep;
    REQUIRE(ep.address() == address);
    REQUIRE(ep.port() == port);
    REQUIRE(ep.isEmpty() == true);
}

TEST_CASE("Construct address and port")
{
    uint32_t address = 9231273;
    uint16_t port = 1358;
    OpenMX::EndPoint ep(address, port);
    REQUIRE(ep.address() == address);
    REQUIRE(ep.port() == port);
    REQUIRE(ep.isEmpty() == false);
}

TEST_CASE("Try parse hash")
{
    std::string hash = "0100007F1A2B";
    uint32_t address = 16777343;
    uint16_t port = 6699;
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(hash));
    auto ep = OpenMX::EndPoint::tryParse(hash);
    REQUIRE(ep.has_value() == true);
    REQUIRE(ep.value() == OpenMX::EndPoint(address, port));
}

TEST_CASE("Try parse hash invalid port")
{
    std::string hash = "0100007F1G2B";
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(hash));
    auto ep = OpenMX::EndPoint::tryParse(hash);
    REQUIRE(ep.has_value() == false);
}

TEST_CASE("Try parse hash invalid IP")
{
    std::string hash = "0100Z07F1A2B";
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(hash));
    auto ep = OpenMX::EndPoint::tryParse(hash);
    REQUIRE(ep.has_value() == false);
}

TEST_CASE("Try parse hash with end padding")
{
    std::string hash = "0100007F1A2BA";
    uint32_t address = 16777343;
    uint16_t port = 6699;
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(hash));
    auto ep = OpenMX::EndPoint::tryParse(hash);
    REQUIRE(ep.has_value() == true);
    REQUIRE(ep.value() == OpenMX::EndPoint(address, port));
}

TEST_CASE("Try parse hash missing a character")
{
    std::string hash = "0100007F1A2";
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(hash));
    auto ep = OpenMX::EndPoint::tryParse(hash);
    REQUIRE(ep.has_value() == false);
}

TEST_CASE("Try parse ip:port")
{
    std::string hash = "127.0.0.1:6699";
    uint32_t address = 16777343;
    uint16_t port = 6699;
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(hash));
    auto ep = OpenMX::EndPoint::tryParse(hash);
    REQUIRE(ep.has_value() == true);
    REQUIRE(ep.value() == OpenMX::EndPoint(address, port));
}

TEST_CASE("Try parse ip:port invalid IP")
{
    std::string hash = "127.0.300.1:6699";
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(hash));
    auto ep = OpenMX::EndPoint::tryParse(hash);
    REQUIRE(ep.has_value() == false);
}

TEST_CASE("Try parse ip:port invalid port")
{
    std::string hash = "127.0.0.1:65536";
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(hash));
    auto ep = OpenMX::EndPoint::tryParse(hash);
    REQUIRE(ep.has_value() == false);
}

TEST_CASE("Try parse semicolor only")
{
    std::string hash = ":";
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(hash));
    auto ep = OpenMX::EndPoint::tryParse(hash);
    REQUIRE(ep.has_value() == false);
}

TEST_CASE("Try parse ip and port")
{
    std::string addr = "127.0.0.1";
    std::string port = "6699";
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(addr, port));
    auto ep = OpenMX::EndPoint::tryParse(addr, port);
    REQUIRE(ep.has_value() == true);
    REQUIRE(ep.value() == OpenMX::EndPoint(16777343, 6699));
}

TEST_CASE("Try parse ip and port invalid ip")
{
    std::string addr = "127.00.1";
    std::string port = "6699";
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(addr, port));
    auto ep = OpenMX::EndPoint::tryParse(addr, port);
    REQUIRE(ep.has_value() == false);
}

TEST_CASE("Try parse ip and port invalid port")
{
    std::string addr = "127.0.0.1";
    std::string port = "6699a";
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(addr, port));
    auto ep = OpenMX::EndPoint::tryParse(addr, port);
    REQUIRE(ep.has_value() == false);
}

TEST_CASE("Try parse ip and port empty ip")
{
    std::string addr = "";
    std::string port = "6699a";
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(addr, port));
    auto ep = OpenMX::EndPoint::tryParse(addr, port);
    REQUIRE(ep.has_value() == false);
}

TEST_CASE("Try parse ip and port empty port")
{
    std::string addr = "192.168.0.1";
    std::string port = "";
    REQUIRE_NOTHROW(OpenMX::EndPoint::tryParse(addr, port));
    auto ep = OpenMX::EndPoint::tryParse(addr, port);
    REQUIRE(ep.has_value() == false);
}