#define _GLIBCXX_USE_NANOSLEEP

#include <algorithm>
#include <thread>
#include <iostream>
#include <tgmath.h>
#include <fstream>
#include <iomanip>

#include "ProcessControl.h"
#include "Common.h"
#include "Utils.h"

#define PROPORTIONAL 1
#define SIM_COOLING 0.1

ProcessControl::ProcessControl()
    : _udpInterface(50001) {
    _mode = MODE::MANUAL;
    _currentSegmentIndex = 0;
    _currentTemperature = 0.0;
    _setpoint = 0.0;
}

ProcessControl::~ProcessControl() {
    
}

void ProcessControl::run() {
    float simval = 0.0;
    _segmentStartTime = -1;
    _curveStore.initCurvesFromFile("/brewer_files/brewer_curves.txt");
    _curveStore.saveCurvesToFile("/brewer_files/brewer_curves.txt");
    while (!stopControlRequested) {
        processCommands();
        if (_simulationMode) {
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            _currentTemperature = simval;
            simval = simval + _outputPercent * 0.1 - SIM_COOLING;
        }
        
        if (_mode == MODE::AUTO) {
            std::cout << "current segment duration: " << _currentSegment->getDuration() << std::endl;
            if ((_segmentStartTime > 0) && ((unsigned)(std::time(0) - _segmentStartTime) >= _currentSegment->getDuration())) {
                    if (_currentSegmentIndex == _curveStore.getCurve(_currentCurve)->size() - 1) {
                        _segmentStartTime = -1;
                        stopCurve();
                    } else {
                        _currentSegment = _curveStore.getCurve(_currentCurve)->at(++_currentSegmentIndex);
                        _setpoint = _currentSegment->getSetpoint();
                        _segmentStartTime = -1;
                    }
            } else if (_segmentStartTime < 0) {
                if (fabs(_setpoint - _currentTemperature) < 0.5) {
                    _segmentStartTime = std::time(0);
                }
            }
            if (_segmentStartTime > 0) {
                _timeToNextSegment = _currentSegment->getDuration() - (std::time(0) - _segmentStartTime);
            } else {
                _timeToNextSegment = _currentSegment->getDuration();
            }
        }
        if (_recording) {
            _recordedTemperature.push_back(_currentTemperature);
            _recordedSetpoint.push_back(_setpoint);
        }
        calculatePIDOutput();
        printState();
        writeXML();
    }
}

void ProcessControl::playCurve(std::string name) {
    CurvePtr curve = _curveStore.getCurve(name);
    if (curve->size()) {
        _currentCurve = name;
        _currentSegment = curve->at(0);
        _setpoint = _currentSegment->getSetpoint();
        std::cout << "setpoint set to: " << _setpoint << std::endl;
        _mode = MODE::AUTO;
        startRecording();
    }
}

void ProcessControl::stopCurve() {
    _mode = MODE::MANUAL;
    _setpoint = 0;
    _currentSegmentIndex = 0;
    _segmentStartTime = -1;
    stopRecording();
}

void ProcessControl::processCommands() {
    for (auto msg : _udpInterface.getMessages()) {
        processCommand(std::string(msg));
    }
}

void ProcessControl::processCommand(std::string message) {
    _lastCommand = message;
    /* if (message.substr(0, 8) == "setpoint") {
        // TODO: exception handling
        _setpoint = stod(message.substr(8));
    } else if (message.substr(0, 15) == "get_temperature"){
        std::string temp = "temp: " + std::to_string(_currentTemperature) + "\n";
        _tcpInterface->sendMessage(temp);
    } else if (message.substr(0, 12) == "get_setpoint"){
        std::string setpoint_str = "sp: " + std::to_string(_setpoint) + "\n";
        _tcpInterface->sendMessage(setpoint_str); */
    if (message.substr(0, 12) == "inc_setpoint"){
        _setpoint++;
    } else if (message.substr(0, 12) == "dec_setpoint"){
        _setpoint--;
    }/*  else if (message.substr(0, 9) == "playcurve"){
        playCurve(message.substr(10, message.length()));
    } else if (message.substr(0, 10) == "get_curves"){
        _tcpInterface->sendMessage(_curveStore.getCurveNames() + "\n");
    } */
}

void ProcessControl::writeXML() {
    std::ofstream dataxmlfile;
    dataxmlfile.open ("/var/www/html/data.xml");
    dataxmlfile << "<?xml version=\"1.0\"?>";
    dataxmlfile << "<processdata>\n";
    dataxmlfile << "<temp>" << _currentTemperature << "</temp>\n";
    dataxmlfile << "<setpoint>" << _setpoint << "</setpoint>\n";
    dataxmlfile << "<output>" << _outputPercent << "</output>\n";
    dataxmlfile << "<delta>" << _setpoint - _currentTemperature << "</delta>\n";
    dataxmlfile << "<mode>";
    switch(_mode) {
                      case MODE::MANUAL: dataxmlfile << "MANUAL"; break;
                      case MODE::AUTO: dataxmlfile << "AUTO"; break;
                  };
    dataxmlfile << "</mode>\n";
    dataxmlfile << "<timetonextsegment>" << _timeToNextSegment << "</timetonextsegment>\n";
    dataxmlfile << "</processdata>\n";
    dataxmlfile.close();
}

void ProcessControl::printState() {
    std::system("clear");
    std::cout << "Connection state: \n";
              /* if (_tcpInterface->_connected) {
                  std::cout << "Connected" << "\n";
              } else {
                  std::cout << "Disconnected" << "\n";
              } */
    std::cout << "Current time in seconds: " << std::time(0) << "\n";
              if (_mode == MODE::AUTO) {
                  std::cout << "Number of segments:      " << _curveStore.getCurve(_currentCurve)->size() << "\n"
                            << "Current segment index:   " << _currentSegmentIndex << "\n"
                            << "Time to next segment:    " << _timeToNextSegment << "\n";
              }
    std::cout << "Current temperature:        " << _currentTemperature << "\n"
              << "Current ouput percentage:   " << _outputPercent << "\n"
              << "Setpoint:                   " << _setpoint << "\n"
              << "Delta                       " << _setpoint - _currentTemperature << "\n"
              << "Current Mode:               ";
              switch(_mode) {
                  case MODE::MANUAL: std::cout << "MANUAL\n"; break;
                  case MODE::AUTO: std::cout << "AUTO\n"; break;
              };
              std::cout << "Last command received: " << _lastCommand << std::endl;
}

void ProcessControl::startRecording() {
    _recordingStartTime = std::time(0);
    _recording = true;
}

void ProcessControl::stopRecording() {
    _recording = false;
    std::ofstream historyfile;
    historyfile.open ("/brewer_files/history/" + _currentCurve + "_" + std::to_string(_recordingStartTime) + ".txt");
    for (unsigned i = 0; i < _recordedTemperature.size(); i++) {
        if (i) {
            historyfile << ";" << std::setprecision(2) << _recordedTemperature[i];
        } else {
            historyfile << std::setprecision(2) << _recordedTemperature[i];
        }
    }
    historyfile << "\n";
    for (unsigned i = 0; i < _recordedSetpoint.size(); i++) {
        if (i) {
            historyfile << ";" << std::setprecision(2) << _recordedSetpoint[i];
        } else {
            historyfile << std::setprecision(2) << _recordedSetpoint[i];
        }
    }
    _recordedTemperature.clear();
    _recordedSetpoint.clear();
}

void ProcessControl::calculatePIDOutput() {
    if (_setpoint < 20) {
        _outputPercent = 0;
    } else {
        _outputPercent = std::max(std::min(float(100.0), PROPORTIONAL * (_setpoint - _currentTemperature) / _setpoint * 100), float(0.0));
    }
}

