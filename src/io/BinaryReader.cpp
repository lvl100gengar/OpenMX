#include "BinaryReader.h"
#include <memory>
#include <stdexcept>

namespace OpenMX {
namespace io {

    BinaryReader::BinaryReader(const char* buffer, size_t capacity)
        : m_buffer(buffer)
        , m_currentPosition(0)
        , m_bufferCapacity(capacity)
    {
    }

    size_t BinaryReader::capacity() const {
        return m_bufferCapacity;
    }

    void BinaryReader::skip(size_t count) {
        m_currentPosition += count;
    }

    void BinaryReader::setBuffer(size_t position, size_t capacity)
    {
        m_currentPosition = position;
        m_bufferCapacity = capacity;
    }

    bool BinaryReader::canRead(size_t readSize) const
    {
        return readSize < INT16_MAX && (m_currentPosition + readSize) <= m_bufferCapacity;
    }

    uint8_t BinaryReader::readByte()
    {
        if (!canRead(1))
            throw std::runtime_error("Attempted to read beyond buffer capacity.");

        return m_buffer[m_currentPosition++];
    }

    uint16_t BinaryReader::readShort()
    {
        if (!canRead(2))
            throw std::runtime_error("Attempted to read beyond buffer capacity.");

        uint16_t result = 0;
        result |= m_buffer[m_currentPosition + 0] << 8;
        result |= m_buffer[m_currentPosition + 1];
        m_currentPosition += 2;
        return result;
    }

    uint32_t BinaryReader::readInt()
    {
        if (!canRead(4))
            throw std::runtime_error("Attempted to read beyond buffer capacity.");

        uint32_t result = 0;
        result |= m_buffer[m_currentPosition + 0] << 24;
        result |= m_buffer[m_currentPosition + 1] << 16;
        result |= m_buffer[m_currentPosition + 2] << 8;
        result |= m_buffer[m_currentPosition + 3];
        m_currentPosition += 4;
        return result;
    }

    uint64_t BinaryReader::readLong()
    {
        if (!canRead(8))
            throw std::runtime_error("Attempted to read beyond buffer capacity.");

        uint64_t result = 0;
        result |= (uint64_t)m_buffer[m_currentPosition + 0] << 56;
        result |= (uint64_t)m_buffer[m_currentPosition + 1] << 48;
        result |= (uint64_t)m_buffer[m_currentPosition + 2] << 40;
        result |= (uint64_t)m_buffer[m_currentPosition + 3] << 32;
        result |= (uint64_t)m_buffer[m_currentPosition + 4] << 24;
        result |= (uint64_t)m_buffer[m_currentPosition + 5] << 16;
        result |= (uint64_t)m_buffer[m_currentPosition + 6] << 8;
        result |= (uint64_t)m_buffer[m_currentPosition + 7];
        m_currentPosition += 8;
        return result;
    }

    std::string BinaryReader::readString()
    {
        size_t nullTerminatorIndex = m_bufferCapacity;

        for (size_t i = m_currentPosition; i < m_bufferCapacity; i++) {
            if (m_buffer[i] == '\0') {
                nullTerminatorIndex = i;
                break;
            }
        }

        // Ex: 2 byte buffer
        // 0 1 2
        //     ^ if no null found: stringLength=2, currentPos=3
        //   ^   if string is 1 char with null: stringLength=1, currentPos=2

        size_t stringLength = nullTerminatorIndex - m_currentPosition;

        if (!canRead(stringLength))
            throw std::runtime_error("Attempted to read beyond buffer capacity.");

        auto result = std::string(m_buffer + m_currentPosition, stringLength);
        m_currentPosition += stringLength + 1;
        return result;
    }

    std::string BinaryReader::readString(size_t length)
    {
        if (!canRead(length))
            throw std::runtime_error("Attempted to read beyond buffer capacity.");

        return std::string(m_buffer + m_currentPosition, length);
    }

    uint8_t* BinaryReader::readBytes(size_t count)
    {
        if (!canRead(count))
            throw std::runtime_error("Attempted to read beyond buffer capacity.");

        uint8_t* result = new uint8_t[count];
        std::copy(m_buffer + m_currentPosition, m_buffer + m_currentPosition + count, result);
        m_currentPosition += count;
        return result;
    }

} // namespace io
} // namespace OpenMX