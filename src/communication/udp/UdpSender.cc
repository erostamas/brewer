#include "UdpSender.h"

#include <string>

UdpSender::UdpSender(const std::string& ipAddress, unsigned port)
    : _remoteEndpoint(boost::asio::ip::address::from_string(ipAddress), port) {
    using namespace boost::asio;
    io_service ioService;
    _socket = std::unique_ptr<ip::udp::socket>(new ip::udp::socket(ioService));
    _socket->open(ip::udp::v4());
}

UdpSender::~UdpSender() {
    _socket->close();
}

void UdpSender::send(const char* message, std::size_t length) {
    boost::system::error_code err;
    _socket->send_to(boost::asio::buffer(message, length), _remoteEndpoint, 0, err);
}

void UdpSender::send(const std::string& message) {
    send(message.c_str(), message.size());
}
