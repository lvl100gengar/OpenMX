#include "protocol/RoomName.h"

#include "../catch.hpp"

#include <string>

TEST_CASE("Construct from string")
{
    std::string name = "test";
    OpenMX::RoomName room(name);
    REQUIRE(room.name() == name);
}

TEST_CASE("Validate empty string")
{
    std::string name = "";
    OpenMX::RoomName room(name);
    REQUIRE_NOTHROW(room.isValid());
    REQUIRE(room.isValid() == false);
    REQUIRE_NOTHROW(room.endPoint());
    REQUIRE(room.endPoint().has_value() == false);
}

TEST_CASE("Validate '_' string")
{
    std::string name = "_";
    OpenMX::RoomName room(name);
    REQUIRE_NOTHROW(room.isValid());
    REQUIRE(room.isValid() == false);
    REQUIRE_NOTHROW(room.endPoint());
    REQUIRE(room.endPoint().has_value() == false);
}

TEST_CASE("Validate name with no hash")
{
    std::string name = "name_";
    OpenMX::RoomName room(name);
    REQUIRE_NOTHROW(room.isValid());
    REQUIRE(room.isValid() == false);
    REQUIRE_NOTHROW(room.endPoint());
    REQUIRE(room.endPoint().has_value() == false);
}

TEST_CASE("Validate name and ip with no port")
{
    std::string name = "name_0100007F";
    OpenMX::RoomName room(name);
    REQUIRE_NOTHROW(room.isValid());
    REQUIRE(room.isValid() == false);
    REQUIRE_NOTHROW(room.endPoint());
    REQUIRE(room.endPoint().has_value() == false);
}

TEST_CASE("Validate 'name_0100007F1446' string")
{
    std::string name = "name_0100007F1446";
    OpenMX::RoomName room(name);
    REQUIRE_NOTHROW(room.isValid());
    REQUIRE(room.isValid() == true);
    REQUIRE_NOTHROW(room.endPoint());
    REQUIRE(room.endPoint().has_value() == true);
}

TEST_CASE("Validate '_0100007F1446' string")
{
    std::string name = "_0100007F1446";
    OpenMX::RoomName room(name);
    REQUIRE_NOTHROW(room.isValid());
    REQUIRE(room.isValid() == false);
    REQUIRE_NOTHROW(room.endPoint());
}

TEST_CASE("Validate 'name_127.0.0.1:1234' string")
{
    std::string name = "name_127.0.0.1:1234";
    OpenMX::RoomName room(name);
    REQUIRE_NOTHROW(room.isValid());
    REQUIRE(room.isValid() == true);
    REQUIRE_NOTHROW(room.endPoint());
    REQUIRE(room.endPoint().has_value() == true);
}

TEST_CASE("Validate 'name_127.0.1:1234' string")
{
    std::string name = "name_127.0.1:1234";
    OpenMX::RoomName room(name);
    REQUIRE_NOTHROW(room.isValid());
    REQUIRE(room.isValid() == false);
    REQUIRE_NOTHROW(room.endPoint());
    REQUIRE(room.endPoint().has_value() == false);
}

TEST_CASE("Validate 'na_me_0100007F1446' string")
{
    std::string name = "na_me_0100007F1446";
    OpenMX::RoomName room(name);
    REQUIRE_NOTHROW(room.isValid());
    REQUIRE(room.isValid() == true);
    REQUIRE_NOTHROW(room.endPoint());
    REQUIRE(room.endPoint().has_value() == true);
}