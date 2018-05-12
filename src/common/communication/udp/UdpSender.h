#pragma once

#include <boost/asio.hpp>
#include <string>
#include <memory>

class UdpSender {
    void init();

public:
    UdpSender(const std::string& ipAddress, unsigned port);
    UdpSender(boost::asio::ip::udp::endpoint remoteEndpoint);
    ~UdpSender();

    void send(const char* message, std::size_t length);
    void send(const std::string& message);

private:
    boost::asio::io_service _ioService;
    std::unique_ptr<boost::asio::ip::udp::socket> _socket;
    boost::asio::ip::udp::endpoint _remoteEndpoint;
};