#include <iostream>
#include <thread>
#include <cstdlib>

#include "TcpInterface.h"

TcpInterface tcpint;

void startListening() {	
	tcpint.init();
}

int main(void) {
    std::cout << "hello world" << std::endl;
	
	std::thread t1(startListening);
	int i = 0;
	while(!tcpint.exit_command) {
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
		std::cout << i << std::endl;
	    i++;
	}
	exit(0);
	
}