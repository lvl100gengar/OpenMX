#include "ConnectionListener.h"

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/yield.hpp>
#include <boost/log/attributes/named_scope.hpp>
#include <boost/log/sources/logger.hpp>
#include <boost/log/sources/record_ostream.hpp>
#include <functional>
#include <memory>

namespace OpenMX {

ConnectionListener::ConnectionListener(boost::asio::io_context& context, std::function<void(tcp::socket&& socket, tcp::endpoint& remoteEndPoint)>& callback, boost::log::sources::logger& logger)
    : m_callback(callback)
    , m_context(context)
    , m_logger(logger)
{
}

bool ConnectionListener::start(tcp::endpoint const& localEndPoint)
{
    try {
        // using unique_ptr since acceptor has no default constructor
        m_acceptor = std::make_unique<boost::asio::ip::tcp::acceptor>(m_context, localEndPoint);
    } catch (const std::system_error& e) {
        BOOST_LOG_FUNCTION();
        BOOST_LOG(m_logger) << "Could not create acceptor: " << e.what();
        return false;
    }

    // spawn task to be run on io_context thread
    boost::asio::spawn(m_context, std::bind(&ConnectionListener::acceptLoopAsync, this, std::placeholders::_1));
    return true;
}

void ConnectionListener::stop()
{
    // stop async loop by destroying acceptor object
    m_acceptor.reset();
}

void ConnectionListener::acceptLoopAsync(boost::asio::yield_context yc)
{
    boost::system::error_code ec;

    while (m_acceptor.get() != nullptr) {
        tcp::socket socket(m_context);
        tcp::endpoint remoteEndPoint;

        m_acceptor->async_accept(socket, remoteEndPoint, yc[ec]);

        if (ec) {
            BOOST_LOG_FUNCTION();
            BOOST_LOG(m_logger) << "Accept failed: " << ec;
            continue;
        }

        m_callback(std::move(socket), remoteEndPoint);
    }
}

} // namespace OpenMX