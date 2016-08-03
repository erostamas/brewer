#pragma once

#include <vector>

class TcpInterface {
public:
    void run();
    int bindToPort(int portno);
    int acceptConnection(int sockfd);
    std::vector<std::string> getMessages();
    void sendMessage(std::string);
    void listenForConnection(int sockfd, int portno);
    
    bool _exitCommand;
    std::vector<std::string> _messageQueue;
    int _connectedSocketFd = -1;
    bool _connected;
};