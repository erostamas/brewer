#include <iostream>
#include <thread>
#include <cstdlib>

#include "TcpInterface.h"
#include "UdpInterface.h"
#include "ProcessControl.h"
#include "Common.h"

bool stopControlRequested = false;
double currentTemperature = 0.0;
double setpoint = 0.0;
TcpInterface tcpint;
UdpInterface udpint;

void startTCPListening() {	
	tcpint.run();
}

void startUDPDiscoveryService() {
    udpint.run();
}

int main(void) {
    std::cout << "hello world" << std::endl;
	
	std::thread t1(startTCPListening);
    std::thread t2(startUDPDiscoveryService);
	ProcessControl processcontrol;
    processcontrol.setSimulationMode(true);
    processcontrol.run();
	exit(0);
	
}