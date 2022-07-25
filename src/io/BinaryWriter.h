#pragma once

#include <string>

namespace OpenMX {
namespace io {

    enum StringOptions{
        NullTerminate,
        Raw
    }

    class BinaryWriter {
    private:
        char* m_buffer;
        size_t m_currentPosition;
        size_t m_bufferCapacity;

    public:
        BinaryWriter(char* buffer, size_t capacity);
        bool canWrite(size_t writeSize) const;
        void writeByte(uint8_t value);
        void writeShort(uint16_t value);
        void writeInt(uint32_t value);
        void writeLong(uint64_t value);
        void writeString(const std::string& value, bool nullTerminate);
        void writeBytes(const unsigned char* buffer, size_t startingIndex, size_t count);
    };

} // namespace io
} // namespace OpenMX