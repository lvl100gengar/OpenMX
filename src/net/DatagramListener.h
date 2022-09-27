#pragma once

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <boost/log/sources/logger.hpp>

#include <functional>
#include <list>
#include <memory>

namespace OpenMX {

/**
 * @brief Listens for datagrams on a specified UDP port
 *
 */
class DatagramListener {
private:
    boost::asio::ip::udp::socket m_socket;
    boost::asio::io_context& m_context;
    boost::log::sources::logger m_logger;

    void receiveLoopAsync(boost::asio::yield_context yield);

public:
    DatagramListener(boost::asio::io_context& context, boost::asio::ip::udp::endpoint const& localEndPoint, boost::log::sources::logger& logger);
};

} // namespace OpenMX