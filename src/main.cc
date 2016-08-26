#include <iostream>
#include <thread>
#include <cstdlib>
#include <csignal>

#include "Common.h"
#include "Logging.h"
#include "ProcessControl.h"
#include "TcpInterface.h"

bool stopControlRequested = false;

TcpInterface tcpint;

void startTCPListening() {
	tcpint.run();
}

void signalHandler( int signum ) {
    std::cout << "Interrupt signal received, terminating...\n";
    exit(0);
}

int main(void) {
    init_logging();
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    ProcessControl processcontrol(&tcpint);

	std::thread t1(startTCPListening);
    processcontrol.setSimulationMode(true);
    processcontrol.run();
	exit(0);
}
