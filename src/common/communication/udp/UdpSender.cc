#include "UdpSender.h"

#include <string>
#include <boost/bind.hpp>

#include "Logging.h"

UdpSender::UdpSender(const std::string& ipAddress, unsigned port)
    : _remoteEndpoint(boost::asio::ip::address::from_string(ipAddress), port) {
    init();
}

UdpSender::UdpSender(boost::asio::ip::udp::endpoint remoteEndpoint)
    : _remoteEndpoint(remoteEndpoint) {
    init();
}

UdpSender::~UdpSender() {
    _socket->close();
}

void UdpSender::init() {
    using namespace boost::asio;
    _socket = std::unique_ptr<ip::udp::socket>(new ip::udp::socket(_ioService));
    _socket->open(ip::udp::v4());
}
void UdpSender::send(const char* message, std::size_t length) {
    boost::system::error_code err;
    _socket->send_to(boost::asio::buffer(message, length), _remoteEndpoint, 0, err);
}

void UdpSender::send(const std::string& message) {
    send(message.c_str(), message.size());
}
