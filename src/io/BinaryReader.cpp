#include "BinaryReader.h"
#include <memory>
#include <stdexcept>

namespace OpenMX {
namespace io {

    BinaryReader::BinaryReader(char* buffer, size_t position, size_t capacity)
        : m_buffer(buffer)
        , m_currentPosition(position)
        , m_bufferCapacity(capacity)
    {
    }

    void BinaryReader::setBuffer(size_t position, size_t capacity)
    {
        m_currentPosition=position;
        m_bufferCapacity=capacity;
    }

    bool BinaryReader::canRead(size_t readSize) const
    {
        return (m_currentPosition + readSize) <= m_bufferCapacity;
    }

    unsigned char BinaryReader::readByte()
    {
        if (!canRead(1))
            throw std::runtime_error("Attempted to read beyond buffer capacity.");

        return m_buffer[m_currentPosition++];
    }

    unsigned short BinaryReader::readShort()
    {
        if (!canRead(2))
            throw std::runtime_error("Attempted to read beyond buffer capacity.");

        unsigned short result = (m_buffer[m_currentPosition] << 8) | m_buffer[m_currentPosition + 1];
        m_currentPosition += 2;
        return result;
    }

    unsigned int BinaryReader::readInt()
    {
        if (!canRead(4))
            throw std::runtime_error("Attempted to read beyond buffer capacity.");

        unsigned short result = (m_buffer[m_currentPosition] << 24) | (m_buffer[m_currentPosition + 1] << 16) | (m_buffer[m_currentPosition + 2] << 8) | m_buffer[m_currentPosition + 3];
        m_currentPosition += 4;
        return result;
    }

    unsigned long BinaryReader::readLong()
    {
        if (!canRead(8))
            throw std::runtime_error("Attempted to read beyond buffer capacity.");

        unsigned short result = (m_buffer[m_currentPosition] << 56) | (m_buffer[m_currentPosition + 1] << 48) | (m_buffer[m_currentPosition + 2] << 40) | (m_buffer[m_currentPosition + 3] << 32) | (m_buffer[m_currentPosition + 4] << 24) | (m_buffer[m_currentPosition + 5] << 16) | (m_buffer[m_currentPosition + 6] << 8) | m_buffer[m_currentPosition + 7];
        m_currentPosition += 8;
        return result;
    }

    std::string BinaryReader::readString()
    {
        size_t nullTerminatorIndex = m_bufferCapacity;

        for (size_t i = m_currentPosition; i < m_bufferCapacity; i++) {
            if (!m_buffer[m_currentPosition]) {
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

    char* BinaryReader::readBytes(size_t count)
    {
        if (!canRead(count))
            throw std::runtime_error("Attempted to read beyond buffer capacity.");

        char* result = new char[count];
        std::copy(m_buffer + m_currentPosition, m_buffer + m_currentPosition + count, result);
        m_currentPosition += count;
        return result;
    }

} // namespace io
} // namespace OpenMX