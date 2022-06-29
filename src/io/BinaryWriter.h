#include <string>

namespace OpenMX {
namespace io {

    class BinaryWriter {
    private:
        char* m_buffer;
        size_t m_currentPosition;
        size_t m_bufferCapacity;

    public:
        BinaryWriter(char* buffer, size_t position, size_t capacity);
        bool canWrite(size_t writeSize) const;
        void writeByte(unsigned char value);
        void writeShort(unsigned short value);
        void writeInt(unsigned int value);
        void writeLong(unsigned long value);
        void writeString(const std::string& value, bool nullTerminate);
        void writeBytes(const unsigned char* buffer, size_t startingIndex, size_t count);
    };

} // namespace io
} // namespace OpenMX