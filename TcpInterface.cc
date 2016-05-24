#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#include "TcpInterface.h"
#include "Common.h"

int TcpInterface::bindToPort(int portno) {
    /*
    #include <netinet/in.h>

    struct sockaddr_in {
        short            sin_family;   // e.g. AF_INET
        unsigned short   sin_port;     // e.g. htons(3490)
        struct in_addr   sin_addr;     // see struct in_addr, below
        char             sin_zero[8];  // zero this if you want to
    };

    struct in_addr {
        unsigned long s_addr;  // load with inet_aton()
    };
    */
    int sockfd;
    struct sockaddr_in server_address;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
       std::cout << "TCP ERROR opening socket" << std::endl;
    }

    bzero((char *) &server_address, sizeof(server_address));
    server_address.sin_family = AF_INET;
    server_address.sin_addr.s_addr = INADDR_ANY;
    server_address.sin_port = htons(portno);

    if (bind(sockfd, (struct sockaddr *) &server_address, sizeof(server_address)) < 0) {
             std::cout << "TCP ERROR binding to port: " << portno << std::endl;
    }
    listen(sockfd,5);
    std::cout << "TCP Server listening on port: " << portno << std::endl;
    return sockfd;
}

int TcpInterface::acceptConnection(int sockfd) {
    struct sockaddr_in cli_addr;
    socklen_t clilen = sizeof(cli_addr);
    std::cout << "Waiting for client connection..." << std::endl;
    int newsockfd = accept(sockfd, 
            (struct sockaddr *) &cli_addr, 
            &clilen);
    if (newsockfd < 0) {
        std::cout << "TCP ERROR when accepting client connection" << std::endl;
    }
    std::cout << "Accepted client connection" << std::endl;
    return newsockfd;
}

void TcpInterface::run() {
    int sockfd, newsockfd, n;
    int noread = -1;
    char buffer[256];
    std::string incoming_message;

    sockfd = bindToPort(5000);

	while(incoming_message != "stop") {
        if(noread > 1000 || noread==-1) {
            noread = 0;
            newsockfd = acceptConnection(sockfd);
        }
        if(incoming_message.size() <= 0) { noread++; }
        bzero(buffer,256);
        n = read(newsockfd,buffer,255);
        if (n < 0) {
            std::cout << "TCP ERROR reading from socket, closing socket" << std::endl;
            break;
        }
        incoming_message = buffer;
        processRequest(incoming_message, newsockfd);
	}
	close(newsockfd);
    close(sockfd);
	_exitCommand = true;
}

void TcpInterface::processRequest(std::string message, int& newsockfd) {
    if (message.substr(0, 8) == "setpoint") {
        // TODO: exception handling
        setpoint = stod(message.substr(8));
    } else if (message.substr(0, 15) == "get_temperature"){
        std::string temp = "temp: " + std::to_string(static_cast<long long>(currentTemperature)) + "\n";
        write(newsockfd,(temp).c_str(),temp.length());
    } else if (message.substr(0, 12) == "get_setpoint"){
        std::string setpoint_str = "sp: " + std::to_string(static_cast<long long>(setpoint)) + "\n";
        write(newsockfd,(setpoint_str).c_str(),setpoint_str.length());
    }
    else if (message.substr(0, 12) == "inc_setpoint"){
        setpoint++;
    }
    else if (message.substr(0, 12) == "dec_setpoint"){
        setpoint--;
    }
}