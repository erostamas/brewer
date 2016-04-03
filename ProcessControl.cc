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
            if (simval < 99) {
                simval++;
            } else {
                simval = 0.0;
            }
            std::cout << currentTemperature << " " << setpoint << std::endl;
            
        }
    }
}