#pragma once

#include <vector>

class UnixDomainSocketInterface {
public:
    void run();
    int bindToPath(std::string path);
    int acceptConnection(int sockfd);
    std::vector<std::string> getMessages();
    void listenForConnection(int sockfd);
    
    bool _shouldExit = false;;
    std::vector<std::string> _messageQueue;
    int _connectedSocketFd = -1;
    bool _connected;
};