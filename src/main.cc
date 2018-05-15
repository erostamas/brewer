#include <iostream>
#include <thread>
#include <cstdlib>
#include <csignal>
#include "boost/program_options.hpp"

#include "Common.h"
#include "Logging.h"
#include "ProcessControl.h"
#include "Exceptions.h"

void signalHandler( int signum ) {
    LOG_INFO << "Interrupt signal received, terminating...\n";
    exit(0);
}

int main(int argc, char** argv) {
    init_logging();
    signal(SIGINT, signalHandler);
    signal(SIGTERM, signalHandler);

    namespace po = boost::program_options;
    po::options_description desc("Options");
    desc.add_options()
      ("simulation", "Simulate temperature measurement");

    po::variables_map vm;
    try
    {
      po::store(po::parse_command_line(argc, argv, desc),
                vm);
    }
    catch(po::error& e)
    {
      LOG_ERROR << "Exception during program option parsing" << e.what() << " - " << desc << std::endl;
      return 1;
    }

    ProcessControl processcontrol;
    if ( vm.count("simulation")  )
      {
        LOG_INFO << "Running in simulation mode";
        processcontrol.setSimulationMode(true);
      }

    try {
        processcontrol.run();
    } catch (const NormalShutdown& e) {
        LOG_INFO << "Shutdown command received, exiting brewer and shutting down Raspberry Pi";
        system("shutdown -P now");
    }
	return 0;
}
