#include "DatagramListener.h"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <functional>
#include <memory>

using boost::asio::ip::tcp;

namespace OpenMX {

void DatagramListener::receiveLoopAsync(boost::asio::yield_context yield)
{
    boost::system::error_code ec;
    boost::asio::ip::udp::endpoint ep;
    char* buffer[10000];

    for (;;) {
        m_socket.async_receive_from(boost::asio::buffer(buffer), ep, yield[ec]);

        if (ec) {
            BOOST_LOG_FUNCTION();
            BOOST_LOG(m_logger) << "Datagram receive failed: " << ec;
            continue;
        }

        // onResult(std::make_unique<Connection>(m_context, std::move(socket)));
    }
}

DatagramListener::DatagramListener(boost::asio::io_context& context, boost::asio::ip::udp::endpoint const& localEndPoint, boost::log::sources::logger& logger)
    : m_context(context)
    , m_socket(context, localEndPoint)
    , m_logger(logger)
{
    boost::asio::spawn(context, std::bind(&DatagramListener::receiveLoopAsync, this, std::placeholders::_1));
}

} // namespace OpenMX