#pragma once

#include <iostream>
#include <string>
#include <vector>

namespace OpenMX {
namespace io {

    class BinaryReader {
    private:
        char* m_buffer;
        size_t m_currentPosition;
        size_t m_bufferCapacity;

    public:
        BinaryReader(char* buffer, size_t position, size_t capacity);
        
        void setBuffer(size_t position, size_t capacity);
        bool canRead(size_t readSize) const;
        unsigned char readByte();
        unsigned short readShort();
        unsigned int readInt();
        unsigned long readLong();
        std::string readString();
        std::string readString(size_t length);
        char* readBytes(size_t count);
    };

} // namespace io
} // namespace OpenMX