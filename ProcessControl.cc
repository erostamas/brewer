#define _GLIBCXX_USE_NANOSLEEP

#include <thread>
#include <iostream>

#include "ProcessControl.h"
#include "Common.h"

void ProcessControl::run() {
    double simval = 0.0;
    while (!stopControlRequested) {
        if (_simulationMode) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            currentTemperature = simval;
/*             if (simval < 99) {
                simval++;
            } else {
                simval = 0.0;
            } */
            simval = simval + (setpoint - currentTemperature) * 0.1;
            std::system("clear");
            std::cout << "Current temperature: " << currentTemperature << "\n"
                      << "Setpoint:            " << setpoint << std::endl;
            
        }
    }
}