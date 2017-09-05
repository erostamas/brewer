#pragma once

#include <boost/asio.hpp>
#include <string>
#include <memory>

class UdpSender {
public:
    UdpSender(const std::string& ipAddress, unsigned port);
    ~UdpSender();

    void send(const char* message, std::size_t length);
    void send(const std::string& message);

private:
    std::unique_ptr<boost::asio::ip::udp::socket> _socket;
    boost::asio::ip::udp::endpoint _remoteEndpoint;
};