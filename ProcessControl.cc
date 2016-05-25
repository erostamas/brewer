#define _GLIBCXX_USE_NANOSLEEP

#include <thread>
#include <iostream>
#include <tgmath.h>

#include "ProcessControl.h"
#include "Common.h"

ProcessControl::ProcessControl() {
    _mode = MODE::MANUAL;
    _currentSegmentIndex = 0;
}
void ProcessControl::run() {
    double simval = 0.0;
    long start_time = -1;
    initCurves();

    while (!stopControlRequested) {
        if (_simulationMode) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            currentTemperature = simval;
            simval = simval + (setpoint - currentTemperature) * 0.1;
        }
        if (_mode == MODE::AUTO) {
            if ((start_time > 0) && ((std::time(0) - start_time) >= _curveStore.getCurve(_currentCurve)[_currentSegmentIndex].getDuration())) {
                    if (_currentSegmentIndex == _curveStore.getCurve(_currentCurve).size() - 1) {
                        stopCurve();
                    } else {
                        setpoint = _curveStore.getCurve(_currentCurve)[++_currentSegmentIndex].getSetpoint();
                    }
                    start_time = -1;
            } else if (start_time < 0) {
                if (fabs(setpoint - currentTemperature) < 0.5) {
                    start_time = std::time(0);
                }
            }
        }
        
        std::system("clear");
        std::cout << "Current time in seconds: " << std::time(0) << "\n";
                  if (_mode == MODE::AUTO) {
                      std::cout << "Number of segments:      " << _curveStore.getCurve(_currentCurve).size() << "\n"
                                << "Current segment index:   " << _currentSegmentIndex << "\n"
                                << "Time to next segment:    ";
                                if (start_time > 0) {
                                    std::cout << _curveStore.getCurve(_currentCurve)[_currentSegmentIndex].getDuration() - (std::time(0) - start_time) << "\n";
                                } else {
                                    std::cout << _curveStore.getCurve(_currentCurve)[_currentSegmentIndex].getDuration() << "\n";
                                }
                  }
        std::cout << "Current temperature:     " << currentTemperature << "\n"
                  << "Setpoint:                " << setpoint << "\n"
                  << "Delta                    " << setpoint - currentTemperature << "\n"
                  << "Current Mode:            ";
                  switch(_mode) {
                      case MODE::MANUAL: std::cout << "MANUAL"; break;
                      case MODE::AUTO: std::cout << "AUTO"; break;
                  };
        std::cout << std::endl;
    }
}

void ProcessControl::initCurves() {
    Segment first(30,10);
    Segment second(40,10);
    Curve curve;
    curve.push_back(first);
    curve.push_back(second);
    _curveStore.addCurve("x", curve);
    //playCurve("x");
}

void ProcessControl::playCurve(std::string name) {
    _currentCurve = name;
    _mode = MODE::AUTO;
    setpoint = _curveStore.getCurve(_currentCurve)[0].getSetpoint();
}

void ProcessControl::stopCurve() {
    _mode = MODE::MANUAL;
    setpoint = 0;
}