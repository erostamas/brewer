class UdpInterface {
public:
    void run();
    int bindToPort(int portno);
private:
    std::string _wireIpAddress;
};