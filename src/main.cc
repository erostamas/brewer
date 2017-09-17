#include <iostream>
#include <thread>
#include <cstdlib>
#include <csignal>

#include "Common.h"
#include "Logging.h"
#include "ProcessControl.h"
#include "UnixDomainSocketInterface.h"

bool stopControlRequested = false;

UnixDomainSocketInterface unixint;

void startUnixDomainListening() {
	unixint.run();
}

void signalHandler( int signum ) {
    LOG_INFO << "Interrupt signal received, terminating...\n";
    unlink("/var/run/brewer/brewer_socket_file");
    exit(0);
}

int main(void) {
    init_logging();
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    ProcessControl processcontrol;

    //std::thread t2(startUnixDomainListening);
    processcontrol.setSimulationMode(true);
    processcontrol.run();
	exit(0);
}
