#include "Listener.h"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <memory>
#include <functional>

using boost::asio::ip::tcp;

namespace OpenMX {

void ConnectionListener::acceptLoopAsync(boost::asio::yield_context yield)
{
    boost::system::error_code ec;

    for (;;) {
        tcp::socket socket(m_context);
        m_acceptor.async_accept(socket, yield[ec]);

        if (ec) {
            BOOST_LOG_FUNCTION();
            BOOST_LOG(m_logger) << "Accept failed: " << ec;
            continue;
        }

        onResult(std::make_unique<Connection>(m_context, std::move(socket)));
    }
}

ConnectionListener::ConnectionListener(boost::asio::io_context& context, boost::asio::ip::tcp::endpoint const& localEndPoint, boost::log::sources::logger& logger)
    : m_context(context)
    , m_acceptor(context, localEndPoint)
    , m_logger(logger)
{
    boost::asio::spawn(context, std::bind(&ConnectionListener::acceptLoopAsync, this, std::placeholders::_1));
}

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

        //onResult(std::make_unique<Connection>(m_context, std::move(socket)));
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