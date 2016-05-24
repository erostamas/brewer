#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <sys/ioctl.h>
#include <net/if.h>
#include <arpa/inet.h>

#include "UdpInterface.h"
#include "Common.h"

int UdpInterface::bindToPort(int portno) {
    struct sockaddr_in serv_addr;
    int sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) {
       std::cout << "UDP ERROR opening socket" << std::endl;
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    struct ifreq ifr;
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
    ioctl(sockfd, SIOCGIFADDR, &ifr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = (((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr).s_addr;
    _wireIpAddress = std::string(inet_ntoa(serv_addr.sin_addr));
    serv_addr.sin_port = htons(portno);
    //std::cout << inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr) << std::endl;
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
             std::cout << "UDP ERROR binding to port: " << portno << std::endl;
    }
    std::cout << "UDP Discovery service bound to " << _wireIpAddress << ":" << portno << std::endl;
    return sockfd;
}
void UdpInterface::run() {
    int sockfd;
    char buffer[256];
    struct sockaddr cli_addr;
    socklen_t clilen = sizeof(cli_addr);

    sockfd = bindToPort(5001);
    std::string message;
    while(1){
        recvfrom(sockfd, buffer, 255, 0, &cli_addr, &clilen);
        std::cout << "recieved message: " << buffer << std::endl;
        message = buffer;
        if (message.substr(0,21) == "where are you brewer?") {
            std::cout << "jap" << std::endl;
            //int n = sendto(sockfd, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr), 15, 0, &cli_addr, clilen);
            int n = sendto(sockfd, _wireIpAddress.c_str(), 15, 0, &cli_addr, clilen);
            if (n<0) {  std::cout << "error sending udp packet" << std::endl;}
        }
    }
}