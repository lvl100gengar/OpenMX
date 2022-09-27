#pragma once

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/log/sources/logger.hpp>
#include <functional>
#include <memory>
#include <optional>

namespace OpenMX {

/**
 * @brief Listens for incoming TCP socket connections on a specified endpoint
 */
class ConnectionListener {
public:
    using tcp = boost::asio::ip::tcp;

    ConnectionListener(boost::asio::io_context& context, std::function<void(tcp::socket&& socket, tcp::endpoint& remoteEndPoint)>& callback, boost::log::sources::logger& logger);
    bool start(boost::asio::ip::tcp::endpoint const& localEndPoint);
    void stop();

private:
    void acceptLoopAsync(boost::asio::yield_context yield);

    std::unique_ptr<boost::asio::ip::tcp::acceptor> m_acceptor;
    std::function<void(tcp::socket&& socket, tcp::endpoint& remoteEndPoint)> m_callback;
    boost::asio::io_context& m_context;
    boost::log::sources::logger m_logger;
};

} // namespace OpenMX