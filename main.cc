#include <iostream>
#include <thread>
#include <cstdlib>

#include "TcpInterface.h"
#include "ProcessControl.h"
#include "Common.h"

bool stopControlRequested = false;
double currentTemperature = 0.0;
double setpoint = 0.0;
TcpInterface tcpint;

void startListening() {	
	tcpint.run();
}

int main(void) {
    std::cout << "hello world" << std::endl;
	
	std::thread t1(startListening);
	ProcessControl processcontrol;
    processcontrol.setSimulationMode(true);
    processcontrol.run();
	exit(0);
	
}