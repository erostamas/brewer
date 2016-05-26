#include <iostream>
#include <thread>
#include <cstdlib>

#include "TcpInterface.h"
#include "UdpInterface.h"
#include "ProcessControl.h"
#include "Common.h"

bool stopControlRequested = false;

TcpInterface tcpint;
UdpInterface udpint;

void startTCPListening() {	
	tcpint.run();
}

void startUDPDiscoveryService() {
    udpint.run();
}

int main(void) {
    ProcessControl processcontrol(&tcpint);
	
	std::thread t1(startTCPListening);
    std::thread t2(startUDPDiscoveryService);
    processcontrol.setSimulationMode(true);
    processcontrol.run();
	exit(0);
	
}