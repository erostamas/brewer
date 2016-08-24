#include <iostream>
#include <thread>
#include <cstdlib>
#include <csignal>

#include "TcpInterface.h"
#include "ProcessControl.h"
#include "Common.h"

bool stopControlRequested = false;

TcpInterface tcpint;

void startTCPListening() {
	tcpint.run();
}

void signalHandler( int signum )
{
    std::cout << "Interrupt signal received, terminating...\n";
    exit(0);

}


int main(void) {
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    ProcessControl processcontrol(&tcpint);

	std::thread t1(startTCPListening);
    processcontrol.setSimulationMode(true);
    processcontrol.run();
	exit(0);

}