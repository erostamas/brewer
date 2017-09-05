#pragma once

#include <string>
#include <thread>
#include <mutex>

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
    void receiveThread();

private:
    unsigned _listenPort = 0;
    std::thread _receiveThread;
};
