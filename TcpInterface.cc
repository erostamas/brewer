#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h> 
#include <sys/socket.h>
#include <netinet/in.h>
#include <iostream>

#include "TcpInterface.h"

void TcpInterface::init() {
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
	std::cout << "jupppi" << std::endl;
    bzero(buffer,256);
	while(buffer[0] != 'h'){
    n = read(newsockfd,buffer,255);
    if (n < 0) std::cout << "ERROR reading from socket" << std::endl;
    //printf("Here is the message: %s\n",buffer);
    n = write(newsockfd,buffer,18);
    if (n < 0) std::cout << "ERROR writing to socket" << std::endl;

	}
	close(newsockfd);
    close(sockfd);
	exit_command = true;
}