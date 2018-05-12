#pragma once

#include <boost/asio.hpp>
#include <list>
#include <mutex>

class UdpReceiver {
public:
    UdpReceiver(boost::asio::io_service& io_service, unsigned listenPort);
    ~UdpReceiver();

    std::list<const char*> getMessages();
private:
    void startReceive();
    void handleReceive(const boost::system::error_code& error
                     , std::size_t bytes_transferred);
    void handleDiscoveryMessage();

    boost::asio::ip::udp::socket _socket;
    boost::asio::ip::udp::endpoint _remoteEndpoint;
    std::array<char, 1024> _recvBuffer;
    std::list<const char*> _messages;
    std::mutex _messageContainerMutex;
};
