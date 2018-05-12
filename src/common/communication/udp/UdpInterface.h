#pragma once

#include <string>
#include <thread>
#include <mutex>
#include <memory>

#include "UdpReceiver.h"

class UdpInterface {
public:
    UdpInterface(unsigned listenPort);

    void sendTo(const std::string& ipAddress
              , unsigned port
              , const char* message
              , std::size_t length);
    void sendTo(const std::string& ipAddress
              , unsigned port
              , std::string message);
    void startReceiveThread();
    void receiveThread();
    std::list<const char*> getMessages();

private:
    unsigned _listenPort = 0;
    std::thread _receiveThread;
    std::unique_ptr<UdpReceiver> _receiver = nullptr;
};

using UdpInterfacePtr = std::unique_ptr<UdpInterface>;
