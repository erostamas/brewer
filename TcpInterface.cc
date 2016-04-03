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

void TcpInterface::run() {
    int sockfd, newsockfd, portno;
    socklen_t clilen;
    char buffer[256];
    struct sockaddr_in serv_addr, cli_addr;
    int n;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) 
       //error("ERROR opening socket");
    bzero((char *) &serv_addr, sizeof(serv_addr));
	std::cout << "nate" << std::endl;
    portno = 5000;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (bind(sockfd, (struct sockaddr *) &serv_addr,
             sizeof(serv_addr)) < 0) 
             std::cout << "ERROR on binding" << std::endl;
    listen(sockfd,5);
    
    clilen = sizeof(cli_addr);
	
    newsockfd = accept(sockfd, 
                (struct sockaddr *) &cli_addr, 
                &clilen);
    if (newsockfd < 0) {
         std::cout << "ERROR on accept" << std::endl;
	}
	std::cout << "Connection established" << std::endl;
    std::string message;
	while(message != "stop"){
    std::cout << "message:" << message << std::endl;
    bzero(buffer,256);
    n = read(newsockfd,buffer,255);
    if (n < 0) {
        std::cout << "ERROR reading from socket" << std::endl;
        break;
    }
    message = buffer;
    processRequest(message, newsockfd);
    n = write(newsockfd,message.c_str(),message.length());
    if (n < 0) {
        std::cout << "ERROR writing to socket" << std::endl;
        break;
    }

	}
	close(newsockfd);
    close(sockfd);
	exit_command = true;
}

void TcpInterface::processRequest(std::string message, int& newsockfd) {
    if (message.substr(0, 8) == "setpoint") {
        // TODO: exception handling
        setpoint = stod(message.substr(8));
    } else if (message.substr(0, 15) == "get_temperature"){
        std::string temp = std::to_string(currentTemperature);
        write(newsockfd,temp.c_str(),temp.length());
    }
    else if (message.substr(0, 12) == "inc_setpoint"){
        setpoint++;
    }
    else if (message.substr(0, 12) == "dec_setpoint"){
        setpoint--;
    }
    
    
}