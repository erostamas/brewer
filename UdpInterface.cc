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

void UdpInterface::run() {
    int sockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr;
    struct sockaddr cli_addr;
    clilen = sizeof(cli_addr);
    sockfd = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
    if (sockfd < 0) 
       //error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
	std::cout << "nate" << std::endl;
    portno = 5001;
    struct ifreq ifr;
    strncpy(ifr.ifr_name, "eth0", IFNAMSIZ-1);
    ioctl(sockfd, SIOCGIFADDR, &ifr);
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = (((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr).s_addr;
    serv_addr.sin_port = htons(portno);
    std::cout << inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr) << std::endl;
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             std::cout << "ERROR on binding" << std::endl;
    std::string message;
    while(1){
        recvfrom(sockfd, buffer, 255, 0, &cli_addr, &clilen);
        std::cout << "recieved message: " << buffer << std::endl;
        message = buffer;
        if (message.substr(0,21) == "where are you brewer?") {
            std::cout << "jap" << std::endl;
            int n = sendto(sockfd, inet_ntoa(((struct sockaddr_in *)&ifr.ifr_addr)->sin_addr), 4, 0, &cli_addr, clilen);
            if (n<0) {  std::cout << "error sending udp packet" << std::endl;}
        }
    }
}