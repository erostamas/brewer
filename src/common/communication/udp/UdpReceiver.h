#pragma once

#include <boost/asio.hpp>
#include <list>

class UdpReceiver {
public:
    UdpReceiver(boost::asio::io_service& io_service, unsigned listenPort);
    ~UdpReceiver();

    void startReceive();
    void handleReceive(const boost::system::error_code& error
                     , std::size_t bytes_transferred);
private:
    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _remoteEndpoint;
    std::array<char, 1024> _recvBuffer;
    std::list<const char*> _messages;
};
