#include "BinaryWriter.h"
#include <cassert>

namespace OpenMX {
namespace io {

    BinaryWriter::BinaryWriter(char* buffer, size_t position, size_t capacity)
        : m_buffer(buffer)
        , m_currentPosition(position)
        , m_bufferCapacity(capacity)
    {
    }

    bool BinaryWriter::canWrite(size_t writeSize) const
    {
        return (m_currentPosition + writeSize) <= m_bufferCapacity;
    }

    void BinaryWriter::writeByte(uint8_t value)
    {
        assert(canWrite(1));

        m_buffer[m_currentPosition++] = value;
    }

    void BinaryWriter::writeShort(uint16_t value)
    {
        assert(canWrite(2));

        m_buffer[m_currentPosition + 0] = (value >> 8) & 0xFF;
        m_buffer[m_currentPosition + 1] = (value >> 0) & 0xFF;
        m_currentPosition += 2;
    }

    void BinaryWriter::writeInt(uint32_t value)
    {
        assert(canWrite(4));

        m_buffer[m_currentPosition + 0] = (value >> 24) & 0xFF;
        m_buffer[m_currentPosition + 1] = (value >> 16) & 0xFF;
        m_buffer[m_currentPosition + 2] = (value >> 8) & 0xFF;
        m_buffer[m_currentPosition + 3] = (value >> 0) & 0xFF;
        m_currentPosition += 4;
    }

    void BinaryWriter::writeLong(uint64_t value)
    {
        assert(canWrite(8));

        m_buffer[m_currentPosition + 0] = (value >> 56) & 0xFF;
        m_buffer[m_currentPosition + 1] = (value >> 48) & 0xFF;
        m_buffer[m_currentPosition + 2] = (value >> 40) & 0xFF;
        m_buffer[m_currentPosition + 3] = (value >> 32) & 0xFF;
        m_buffer[m_currentPosition + 4] = (value >> 24) & 0xFF;
        m_buffer[m_currentPosition + 5] = (value >> 16) & 0xFF;
        m_buffer[m_currentPosition + 6] = (value >> 8) & 0xFF;
        m_buffer[m_currentPosition + 7] = (value >> 0) & 0xFF;
        m_currentPosition += 8;
    }

    void BinaryWriter::writeString(const std::string& value, bool nullTerminate)
    {
        assert(canWrite(value.size() + (nullTerminate ? 1 : 0)));

        value.copy(m_buffer + m_currentPosition, value.size(), 0);

        // string of size 2
        // 0 1 2 3 4
        // a b 0

        if (nullTerminate) {
            m_buffer[m_currentPosition + value.size()] = 0;
            m_currentPosition += value.size() + 1;
        } else
            m_currentPosition += value.size();
    }

    void BinaryWriter::writeBytes(const unsigned char* value, size_t startingIndex, size_t count)
    {
        assert(canWrite(count));

        std::copy(value + startingIndex, value + startingIndex + count, m_buffer + m_currentPosition);
        m_currentPosition += count;
    }

} // namespace io
} // namespace OpenMX