#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace OpenMX {

class BinaryReader {
private:
    const char* m_buffer;
    size_t m_currentPosition;
    size_t m_bufferCapacity;

public:
    BinaryReader(const char* buffer, size_t capacity);

    size_t capacity() const;
    void setBuffer(size_t position, size_t capacity);
    void skip(size_t count);
    bool canRead(size_t readSize) const;
    uint8_t readByte();
    uint16_t readShort();
    uint32_t readInt();
    uint64_t readLong();
    std::string readString();
    std::string readString(size_t length);
    uint8_t* readBytes(size_t count);
};

} // namespace OpenMX