#include <iostream>
#include <thread>
#include <cstdlib>
#include <csignal>

#include "Common.h"
#include "Logging.h"
#include "ProcessControl.h"
#include "Exceptions.h"

void signalHandler( int signum ) {
    LOG_INFO << "Interrupt signal received, terminating...\n";
    exit(0);
}

int main(void) {
    init_logging();
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    ProcessControl processcontrol;

    processcontrol.setSimulationMode(true);
    try {
        processcontrol.run();
    } catch (const NormalShutdown& e) {
        LOG_INFO << "Shutdown command received, exiting brewer and shutting down Raspberry Pi";
        system("shutdown -P now");
    }
	return 0;
}
