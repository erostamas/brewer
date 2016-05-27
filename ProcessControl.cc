#define _GLIBCXX_USE_NANOSLEEP

#include <thread>
#include <iostream>
#include <tgmath.h>
#include <fstream>

#include "ProcessControl.h"
#include "Common.h"
#include "Utils.h"

ProcessControl::ProcessControl(TcpInterface* tcpInterface) : _tcpInterface(tcpInterface) {
    _mode = MODE::MANUAL;
    _currentSegmentIndex = 0;
    _currentTemperature = 0.0;
    _setpoint = 0.0;
}

ProcessControl::~ProcessControl() {
    
}

void ProcessControl::run() {
    double simval = 0.0;
    long start_time = -1;
    initCurves();
    std::cout << "1" << std::endl;
    _curveStore.saveCurves();
    std::cout << "2" << std::endl;
    while (!stopControlRequested) {
        processCommands();
        if (_simulationMode) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            _currentTemperature = simval;
            simval = simval + (_setpoint - _currentTemperature) * 0.1;
        }
        if (_mode == MODE::AUTO) {
            if ((start_time > 0) && ((std::time(0) - start_time) >= _currentSegment->getDuration())) {
                    if (_currentSegmentIndex == _curveStore.getCurve(_currentCurve).size() - 1) {
                        stopCurve();
                    } else {
                        _currentSegment = _curveStore.getCurve(_currentCurve)[++_currentSegmentIndex];
                        _setpoint = _currentSegment->getSetpoint();
                    }
                    start_time = -1;
            } else if (start_time < 0) {
                if (fabs(_setpoint - _currentTemperature) < 0.5) {
                    start_time = std::time(0);
                }
            }
        }
        if (start_time > 0) {
            _timeToNextSegment = _currentSegment->getDuration() - (std::time(0) - start_time);
        } else {
            _timeToNextSegment = _currentSegment->getDuration();
        }
        printState();
        writeXML();
    }
}

void ProcessControl::initCurves() {
    if (!Utils::fileExists("/brewer_files/brewer_curves.txt")) {
        return;
    } else {
        std::ifstream curvefile("/brewer_files/brewer_curves.txt");
        std::string line;
        while (std::getline(curvefile, line))
        {
            const std::vector<std::string> v = Utils::split(line, ' ');
            if (v.size() != 2) {
                std::cout << "Error in curve definition" << std::endl;
            } else {
                if(_curveStore.addCurve(v[0], v[1])) {
                    std::cout << "Initialized curve: " << v[0] << std::endl;
                }
            }
        }
    }
}

void ProcessControl::playCurve(std::string name) {
    _currentCurve = name;
    _mode = MODE::AUTO;
    _currentSegment = _curveStore.getCurve(_currentCurve)[0];
    _setpoint = _currentSegment->getSetpoint();
}

void ProcessControl::stopCurve() {
    _mode = MODE::MANUAL;
    _setpoint = 0;
}

void ProcessControl::processCommands() {
    std::vector<std::string> commandqueue = _tcpInterface->getMessages();
    while (commandqueue.size()) {
        processCommand(commandqueue[0]);
        commandqueue.erase(commandqueue.begin());
    }
}

void ProcessControl::processCommand(std::string message) {
    if (message.substr(0, 8) == "setpoint") {
        // TODO: exception handling
        _setpoint = stod(message.substr(8));
    } else if (message.substr(0, 15) == "get_temperature"){
        std::string temp = "temp: " + std::to_string(_currentTemperature) + "\n";
        _tcpInterface->sendMessage(temp);
    } else if (message.substr(0, 12) == "get_setpoint"){
        std::string setpoint_str = "sp: " + std::to_string(_setpoint) + "\n";
        _tcpInterface->sendMessage(setpoint_str);
    }
    else if (message.substr(0, 12) == "inc_setpoint"){
        _setpoint++;
    }
    else if (message.substr(0, 12) == "dec_setpoint"){
        _setpoint--;
    }
    else if (message.substr(0, 9) == "playcurve"){
        playCurve(message.substr(10, message.length()));
    }
}

void ProcessControl::writeXML() {
    std::ofstream myfile;
    myfile.open ("/var/www/html/data.xml");
    myfile << "<?xml version=\"1.0\"?>";
    myfile << "<processdata>\n";
    myfile << "<temp>" << _currentTemperature << "</temp>\n";
    myfile << "<setpoint>" << _setpoint << "</setpoint>\n";
    myfile << "<delta>" << _setpoint - _currentTemperature << "</delta>\n";
    myfile << "<mode>";
    switch(_mode) {
                      case MODE::MANUAL: myfile << "MANUAL"; break;
                      case MODE::AUTO: myfile << "AUTO"; break;
                  };
    myfile << "</mode>\n";
    myfile << "<timetonextsegment>" << _timeToNextSegment << "</timetonextsegment>\n";
    myfile << "</processdata>\n";
    myfile.close();
}

void ProcessControl::printState() {
    std::system("clear");
    std::cout << "Current time in seconds: " << std::time(0) << "\n";
              if (_mode == MODE::AUTO) {
                  std::cout << "Number of segments:      " << _curveStore.getCurve(_currentCurve).size() << "\n"
                            << "Current segment index:   " << _currentSegmentIndex << "\n"
                            << "Time to next segment:    " << _timeToNextSegment << "\n";
              }
    std::cout << "Current temperature:     " << _currentTemperature << "\n"
              << "Setpoint:                " << _setpoint << "\n"
              << "Delta                    " << _setpoint - _currentTemperature << "\n"
              << "Current Mode:            ";
              switch(_mode) {
                  case MODE::MANUAL: std::cout << "MANUAL"; break;
                  case MODE::AUTO: std::cout << "AUTO"; break;
              };
    std::cout << std::endl;
}


