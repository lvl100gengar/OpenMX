#include "Connection.h"

namespace OpenMX {

Connection::Connection(boost::asio::io_context& context, boost::asio::ip::tcp::socket& socket)
    : m_context(context)
    , m_socket(socket)
{
}

void Connection::send(char* buffer, size_t count)
{
}
void Connection::receive(char* buffer, size_t count)
{
}

} // namespace OpenMX