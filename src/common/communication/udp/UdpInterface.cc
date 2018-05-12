#include <iostream>

#include "UdpInterface.h"
#include "UdpSender.h"
#include "UdpReceiver.h"
#include "Logging.h"

UdpInterface::UdpInterface(unsigned listenPort)
    : _listenPort(listenPort) {
}

void UdpInterface::startReceiveThread() {
    _receiveThread = std::thread(&UdpInterface::receiveThread, this);
}

void UdpInterface::sendTo(const std::string& ipAddress
                        , unsigned port
                        , const char* message
                        , std::size_t length) {
    UdpSender sender(ipAddress, port);
    sender.send(message, length);
}

void UdpInterface::sendTo(const std::string& ipAddress
                        , unsigned port
                        , std::string message) {
    sendTo(ipAddress, port, message.c_str(), message.size());
}

void UdpInterface::receiveThread() {
    try {
        LOG_INFO << "[UdpInterface] Listening on port: " << _listenPort;
        boost::asio::io_service ioService;
        _receiver = std::unique_ptr<UdpReceiver>(new UdpReceiver(ioService, _listenPort));
        ioService.run();
    } catch (const std::exception& ex) {
        LOG_ERROR << "[UdpInterface] Exception on receive thread: " << ex.what() << std::endl;
        _receiver = nullptr;
    }
}

std::list<const char*> UdpInterface::getMessages() {
    if (_receiver) {
        return _receiver->getMessages();
    } else {
        std::list<const char*> empty;
        return empty;
    }
}