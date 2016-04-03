

class TcpInterface {
public:
    bool exit_command = false;
    void run();
    void processRequest(std::string, int&);
};