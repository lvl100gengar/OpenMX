#pragma once

#include <boost/asio/ip/tcp.hpp>
#include <chrono>

namespace OpenMX {

class EndPoint;

struct Connection {
    boost::asio::ip::tcp::socket& socket;
    boost::asio::ip::tcp::endpoint& remoteEndPoint;

    using clock = std::chrono::system_clock;
    clock::time_point lastActivity = { clock::now() };

    std::function<void()> disconnectFunction;

    Connection(boost::asio::ip::tcp::socket&& socket, boost::asio::ip::tcp::endpoint& ep) : socket(socket), remoteEndPoint(ep) {
        
    }

    auto secondsSinceLastActivity() const
    {
        return std::chrono::duration_cast<std::chrono::seconds>(clock::now() - lastActivity).count();
    }
    void resetLastActivity()
    {
        lastActivity = clock::now();
    }
    EndPoint endPoint();
};

} // namespace OpenMX