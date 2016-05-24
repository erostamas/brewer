

class TcpInterface {
public:
    void run();
    int bindToPort(int portno);
    int acceptConnection(int sockfd);
    void processRequest(std::string, int&);

    bool _exitCommand;
};