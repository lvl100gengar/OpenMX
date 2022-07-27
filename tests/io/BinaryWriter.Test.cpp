#include "io/BinaryWriter.h"
#include "../catch.hpp"

using OpenMX::BinaryWriter;

TEST_CASE("Writing a byte")
{
    char buffer[1];
    BinaryWriter writer = BinaryWriter(buffer, 1);

    writer.writeByte(0x64);

    REQUIRE(buffer[0] == 0x64);
}

TEST_CASE("Writing a short")
{
    char buffer[2];
    BinaryWriter writer = BinaryWriter(buffer, 2);

    writer.writeShort(0x6464);

    REQUIRE(buffer[0] == 0x64);
    REQUIRE(buffer[1] == 0x64);
}

TEST_CASE("Writing an int")
{
    char buffer[4];
    BinaryWriter writer = BinaryWriter(buffer, 4);

    writer.writeInt(0x64646464);

    REQUIRE(buffer[0] == 0x64);
    REQUIRE(buffer[1] == 0x64);
    REQUIRE(buffer[2] == 0x64);
    REQUIRE(buffer[3] == 0x64);
}

TEST_CASE("Writing a long")
{
    char buffer[8];
    BinaryWriter writer = BinaryWriter(buffer, 8);

    writer.writeLong(0x6464646464646464);

    REQUIRE(buffer[0] == 0x64);
    REQUIRE(buffer[1] == 0x64);
    REQUIRE(buffer[2] == 0x64);
    REQUIRE(buffer[3] == 0x64);
    REQUIRE(buffer[4] == 0x64);
    REQUIRE(buffer[5] == 0x64);
    REQUIRE(buffer[6] == 0x64);
    REQUIRE(buffer[7] == 0x64);
}

TEST_CASE("Writing several bytes")
{
    char buffer[4];
    BinaryWriter writer = BinaryWriter(buffer, 4);

    unsigned char data[] = {1, 10, 100, 255};
    writer.writeBytes(data, 0, 3);

    REQUIRE(buffer[0] == data[0]);
    REQUIRE(buffer[1] == data[1]);
    REQUIRE(buffer[2] == data[2]);
    REQUIRE(writer.canWrite(1));
}

TEST_CASE("Writing a null-term string")
{
    char buffer[10];
    BinaryWriter writer = BinaryWriter(buffer, 10);

    writer.writeString(std::string("str1"), true);
    writer.writeString(std::string("str2"), true);

    char expected[] = "str1\0str2";

    for (size_t i = 0; i < 10; i++)
    {
        REQUIRE(buffer[i] == expected[i]);
    }
}

TEST_CASE("Writing a unterminated string")
{
    char buffer[10];
    BinaryWriter writer = BinaryWriter(buffer, 10);

    writer.writeString(std::string("abcdefg"), false); // 7 char string
    writer.writeByte(1);

    REQUIRE(buffer[0] == 'a');
    REQUIRE(buffer[1] == 'b');
    REQUIRE(buffer[2] == 'c');
    REQUIRE(buffer[3] == 'd');
    REQUIRE(buffer[4] == 'e');
    REQUIRE(buffer[5] == 'f');
    REQUIRE(buffer[6] == 'g');
    REQUIRE(buffer[7] == 1);
    REQUIRE(writer.canWrite(2));
}

TEST_CASE("Writing an empty string")
{
    char buffer[1];
    BinaryWriter writer = BinaryWriter(buffer, 1);

    writer.writeString("", true);

    REQUIRE(buffer[0] == 0);
}