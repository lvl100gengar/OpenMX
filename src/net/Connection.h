#pragma once

#include <boost/asio/io_context.hpp>
#include <boost/asio/ip/tcp.hpp>
#include <boost/asio/spawn.hpp>
#include <boost/asio/steady_timer.hpp>
#include <boost/asio/write.hpp>

namespace OpenMX {

class Connection : public std::enable_shared_from_this<Connection> {
private:
    boost::asio::ip::tcp::socket& m_socket;
    boost::asio::io_context& m_context;
    
public:
    Connection(boost::asio::io_context& context, boost::asio::ip::tcp::socket& socket);

    void send(char* buffer, size_t count);
    void receive(char* buffer, size_t count);
};

} // namespace OpenMX