#include "io/BinaryReader.h"
#include "../catch.hpp"

using OpenMX::io::BinaryReader;

TEST_CASE("Reading a byte")
{
    const char buffer[] = {0x64};
    BinaryReader reader = BinaryReader(buffer, 1);

    REQUIRE(reader.readByte() == 0x64);
}

TEST_CASE("Reading a short")
{
    const char buffer[] = {0x64, 0x64};
    BinaryReader reader = BinaryReader(buffer, 2);

    REQUIRE(reader.readShort() == 0x6464);
}

TEST_CASE("Reading an int")
{
    const char buffer[] = {0x64, 0x64, 0x64, 0x64};
    BinaryReader reader = BinaryReader(buffer, 4);

    REQUIRE(reader.readInt() == 0x64646464);
}

TEST_CASE("Reading a long")
{
    const char buffer[] = {0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64, 0x64};
    BinaryReader reader = BinaryReader(buffer, 8);

    REQUIRE(reader.readLong() == 0x6464646464646464);
}

TEST_CASE("Reading several bytes")
{
    const char buffer[] = {1, 10, 100, (char)255};
    BinaryReader reader = BinaryReader(buffer, 4);
    
    unsigned char *result = reader.readBytes(3);

    REQUIRE(result[0] == buffer[0]);
    REQUIRE(result[1] == buffer[1]);
    REQUIRE(result[2] == buffer[2]);
    REQUIRE(reader.canRead(1));
}

TEST_CASE("Reading a null-term string")
{
    const char buffer[] = "str1\0str2";
    BinaryReader reader = BinaryReader(buffer, 10);
    
    std::string result1 = reader.readString();
    std::string result2 = reader.readString();

    REQUIRE(result1 == std::string(buffer));
    REQUIRE(result2 == std::string(buffer + 5));
}

TEST_CASE("Reading a fixed-length string")
{
    const char* buffer = "abcdefg";
    BinaryReader reader = BinaryReader(buffer, 8);
    
    std::string result1 = reader.readString(3);

    REQUIRE(result1 == std::string(buffer, 3));
}

TEST_CASE("Reading an unterminated string")
{
    const char* buffer = "string";
    BinaryReader reader = BinaryReader(buffer, 5);
    
    std::string result1 = reader.readString();

    REQUIRE(result1 == std::string(buffer, 5));
}

TEST_CASE("Reading an empty string")
{
    const char* buffer = "";
    BinaryReader reader = BinaryReader(buffer, 1);
    
    std::string result1 = reader.readString();

    REQUIRE(result1.empty());
}