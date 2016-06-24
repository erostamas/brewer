#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>
#include <ctime>

#include "TcpInterface.h"
#include "Common.h"
#include "ProcessControl.h"

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
    return sockfd;
}

void TcpInterface::listenForConnection(int sockfd, int portno) {
    listen(sockfd,5);
    std::cout << "TCP Server listening on port: " << portno << std::endl;
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
    int sockfd = -1, n;
    char buffer[256];
    std::string incoming_message;
    long last_recieved_time = 0;
    int portno = 5000;
    
    sockfd = bindToPort(portno);
	while(incoming_message != "stop") {
        if((last_recieved_time == 0) || ((std::time(0) - last_recieved_time) > 3)) {
            //_connected = false;
            if(_connectedSocketFd > 0) { close(_connectedSocketFd); }
            _connected = false;
            listenForConnection(sockfd, portno);
            _connectedSocketFd = acceptConnection(sockfd);
            _connected = true;
            last_recieved_time = std::time(0);
            incoming_message = "";
        }
        if(incoming_message.size() > 0) {
            last_recieved_time = std::time(0);
        }
        bzero(buffer,256);
        n = read(_connectedSocketFd,buffer,255);
        if (n < 0) {
            std::cout << "TCP ERROR reading from socket, closing socket" << std::endl;
            //break;
        }
        incoming_message = buffer;
        if (incoming_message.size() > 0) {
            _messageQueue.push_back(incoming_message);
        }
	}
	close(_connectedSocketFd);
    close(sockfd);
	_exitCommand = true;
}

std::vector<std::string> TcpInterface::getMessages() {
    std::vector<std::string> temp_message_queue = _messageQueue;
    _messageQueue.clear();
    return temp_message_queue;
}

void TcpInterface::sendMessage(std::string message) {
    if(/*_connected*/ true) {
        write(_connectedSocketFd,(message).c_str(),message.length());
    }
}