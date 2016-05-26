#pragma once

#include <vector>

class TcpInterface {
public:
    void run();
    int bindToPort(int portno);
    int acceptConnection(int sockfd);
    std::vector<std::string> getMessages();
    void sendMessage(std::string);

    bool _exitCommand;
    std::vector<std::string> _messageQueue;
    int _connectedSocketFd;
    bool _connected;
};