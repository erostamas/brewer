#define _GLIBCXX_USE_NANOSLEEP

#include <algorithm>
#include <thread>
#include <iostream>
#include <tgmath.h>
#include <fstream>
#include <iomanip>
#include <wiringPiSPI.h>

#include "ProcessControl.h"
#include "Common.h"
#include "Utils.h"

#define PROPORTIONAL 1
#define SIM_COOLING 0.1

ProcessControl::ProcessControl()
    : _currentTemperature("temp", Accessibility::READWRITE)
    , _setpoint("setpoint", Accessibility::READWRITE)
    , _outputPercent("output", Accessibility::READWRITE)
    , _mode("mode", Accessibility::READWRITE)
    , _udpInterface(50001)
    , _xmlSerializer("/var/www/html/data.xml") {
    _mode = MODE::MANUAL;
    _currentSegmentIndex = 0;
}

ProcessControl::~ProcessControl() {
}

void ProcessControl::run() {
    if (wiringPiSPISetup (0, 1000000) < 0)
        fprintf (stderr, "SPI Setup failed: %s\n", strerror (errno));

    unsigned char msg[] = {0x80, 0xD0};
    wiringPiSPIDataRW (0, msg, 2);
    std::this_thread::sleep_for(std::chrono::milliseconds(1000));
    msg[0] = 0x00;
    msg[1] = 0x00;
    wiringPiSPIDataRW (0, msg, 2);
    float simval = 0.0;
    _segmentStartTime = -1;
    _curveStore.initCurvesFromFile("/brewer_files/brewer_curves.txt");
    _curveStore.saveCurvesToFile("/brewer_files/brewer_curves.txt");
    while (!stopControlRequested) {
        if (!_simulationMode) {
            int val;
            unsigned char recv[50];
            recv[0] = 0x01;
            recv[1] = 0x00;
            wiringPiSPIDataRW (0, recv, 2);
            val = recv[1];
            val = val << 8;
            recv[0] = 0x02;
            recv[1] = 0x00;
            wiringPiSPIDataRW (0, recv, 2);
            val += recv[1];
            _currentTemperature = ((double)(val) / 32768 * 430.0 - 100.0) * 10 / 3.9;
        }
        processCommands();
        std::this_thread::sleep_for(std::chrono::milliseconds(1000));
        if (_simulationMode) {
            _currentTemperature = simval;
            simval = simval + _outputPercent.get() * 0.1 - SIM_COOLING;
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
                if (fabs(_setpoint.get() - _currentTemperature.get()) < 0.5) {
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
            _recordedTemperature.push_back(_currentTemperature.get());
            _recordedSetpoint.push_back(_setpoint.get());
        }

        calculatePIDOutput();
        _xmlSerializer.serialize();
        std::system("clear");
        std::stringstream ss;
        _xmlSerializer.serialize(ss);
        std::cout << ss.str() << std::endl;
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
     if (message.substr(0, 8) == "setpoint") {
        // TODO: exception handling
        _setpoint = stod(message.substr(8));
    /*} else if (message.substr(0, 15) == "get_temperature"){
        std::string temp = "temp: " + std::to_string(_currentTemperature) + "\n";
        _tcpInterface->sendMessage(temp);
    } else if (message.substr(0, 12) == "get_setpoint"){
        std::string setpoint_str = "sp: " + std::to_string(_setpoint) + "\n";
        _tcpInterface->sendMessage(setpoint_str); */
    } else if (message.substr(0, 12) == "inc_setpoint"){
        _setpoint = _setpoint.get() + 1;
    } else if (message.substr(0, 12) == "dec_setpoint"){
        _setpoint = _setpoint.get() - 1;
    }/*  else if (message.substr(0, 9) == "playcurve"){
        playCurve(message.substr(10, message.length()));
    } else if (message.substr(0, 10) == "get_curves"){
        _tcpInterface->sendMessage(_curveStore.getCurveNames() + "\n");
    } */
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
    if (_setpoint.get() < 20) {
        _outputPercent = 0;
    } else {
        _outputPercent = (int)(std::max(std::min((float)100.0, (float)(PROPORTIONAL * (_setpoint.get() - _currentTemperature.get()) / _setpoint.get() * 100)), float(0.0)));
    }
}
