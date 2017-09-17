#include <boost/bind.hpp>
#include <iostream>

#include "UdpReceiver.h"
#include "Logging.h"

UdpReceiver::UdpReceiver(boost::asio::io_service& io_service, unsigned listenPort)
    : _socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), listenPort)) {
        startReceive();
}

UdpReceiver::~UdpReceiver() {
    for (auto m : _messages) {
        delete[] m;
    }
}

void UdpReceiver::startReceive() {
    _socket.async_receive_from(boost::asio::buffer(_recvBuffer)
                             , _remoteEndpoint
                             , boost::bind(&UdpReceiver::handleReceive
                                        , this
                                        , boost::asio::placeholders::error
                                        , boost::asio::placeholders::bytes_transferred)
                              );
}

void UdpReceiver::handleReceive(const boost::system::error_code& error
                              , std::size_t bytes_transferred) {
        if (!error || error == boost::asio::error::message_size) {
            char* msg = new char[bytes_transferred + 1];
            strncpy(msg, _recvBuffer.data(), bytes_transferred);
            msg[bytes_transferred] = '\0';
            _messages.push_back(msg);
            LOG_DEBUG << "[UdpReceiver] Received message: " << msg;
        }
        startReceive();
}

std::list<const char*> UdpReceiver::getMessages() {
    _messageContainerMutex.lock();
    auto tmp = _messages;
    _messages.clear();
    _messageContainerMutex.unlock();
    return tmp;
}



