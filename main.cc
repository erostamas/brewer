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
ProcessControl processcontrol;

TcpInterface tcpint;
UdpInterface udpint;

void playCurve(std::string name) {
    processcontrol.playCurve(name);
}

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
    processcontrol.setSimulationMode(true);
    processcontrol.run();
	exit(0);
	
}