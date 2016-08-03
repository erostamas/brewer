#include <iostream>
#include <thread>
#include <cstdlib>

#include "TcpInterface.h"
#include "ProcessControl.h"
#include "Common.h"

bool stopControlRequested = false;

TcpInterface tcpint;

void startTCPListening() {	
	tcpint.run();
}

int main(void) {
    ProcessControl processcontrol(&tcpint);
	
	std::thread t1(startTCPListening);
    processcontrol.setSimulationMode(true);
    processcontrol.run();
	exit(0);
	
}