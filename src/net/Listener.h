#pragma once

#include "Connection.h"
#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/ip/udp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>
#include <boost/log/sources/logger.hpp>
#include <functional>
#include <memory>

namespace OpenMX {

/**
 * @brief Base class for Listeners which signal upon receipt of a new result.
 * @tparam TListenResult The result type
 */
template <typename TListenResult>
class ListenerBase {
private:
    using ListenerCallback = std::function<void(TListenResult)>;
    ListenerCallback m_handler;

protected:
    ListenerBase()
        : m_handler([](TListenResult) {})
    {
    }
    void onResult(TListenResult result) { m_handler(std::move(result)); }

public:
    /**
     * @brief Sets the handler function that will be called when a result is available.
     * @param handler callback function
     */
    void setHandler(ListenerCallback handler)
    {
        m_handler(handler ? handler : [](TListenResult) {})
    }
};

/**
 * @brief A listener that only signals when TestListener::signalResult() is called
 * @tparam TListenResult The result type
 */
template <typename TListenResult>
class TestListener : public ListenerBase<TListenResult> {
public:
    /**
     * @brief Invokes the result callback with the specified result
     * @param result The result that will be passed to the callback
     */
    void signalResult(TListenResult result) { this->onResult(result); }
};

/**
 * @brief Listens for incoming TCP socket connections on a specified endpoint
 */
class ConnectionListener : public ListenerBase<std::unique_ptr<Connection>> {
private:
    boost::asio::ip::tcp::acceptor m_acceptor;
    boost::asio::io_context& m_context;
    boost::log::sources::logger m_logger;

    void acceptLoopAsync(boost::asio::yield_context yield);

public:
    ConnectionListener(boost::asio::io_context& context, boost::asio::ip::tcp::endpoint const& localEndPoint, boost::log::sources::logger& logger);
};

/**
 * @brief Listens for datagrams on a specified UDP port
 *
 */
class DatagramListener : public ListenerBase<std::unique_ptr<int>> {
  private:
    boost::asio::ip::udp::socket m_socket;
    boost::asio::io_context& m_context;
    boost::log::sources::logger m_logger;

    void receiveLoopAsync(boost::asio::yield_context yield);

public:
    DatagramListener(boost::asio::io_context& context, boost::asio::ip::udp::endpoint const& localEndPoint, boost::log::sources::logger& logger);
};

} // namespace OpenMX