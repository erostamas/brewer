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
#include "StringCommandAdapter.h"
#include "Logging.h"

#define PROPORTIONAL 1
#define SIM_COOLING 0.1

ProcessControl::ProcessControl(SystemPtr system)
    : _system(system == nullptr ? std::make_shared<System>() : system)
    , _currentTemperature("temp", Accessibility::READWRITE)
    , _resistance("resistance", Accessibility::READWRITE)
    , _setpoint("setpoint", Accessibility::READWRITE)
    , _outputPercent("output", Accessibility::READWRITE)
    , _mode("mode", Accessibility::READWRITE)
    , _timeToNextSegment("time_to_next_segment", Accessibility::READWRITE)
    , _timeLeftOverall("time_left_overall", Accessibility::READWRITE)
    , _currentCurve("current_curve", Accessibility::READWRITE)
    , _commandAdapter(new StringCommandAdapter()) {
    _mode = MODE::MANUAL;
}

ProcessControl::~ProcessControl() {
}

void ProcessControl::run() {
    _commandAdapter->startCommandReceiver();
    initSPI();
    configureMax31865();
    float simval = 0.0;
    while (true) {
        if (!_simulationMode) {
            readTemperature();
        } else {
            _currentTemperature = simval;
            simval = std::min(std::max(simval + _outputPercent.get() * 0.1 - SIM_COOLING, 15.0), 100.0);
            std::this_thread::sleep_for(std::chrono::milliseconds(500));
        }
        processCommands();

        if (_mode == MODE::AUTO) {
            if (_curvePlayer.getState() == CurvePlayerState::IDLE) {
                _mode = MODE::MANUAL;
                _currentCurve = "";
            } else {
                _curvePlayer.step();
                _setpoint = _curvePlayer.getCurrentSetpoint();
                _timeToNextSegment = _curvePlayer.getTimeToNextSegment();
                _timeLeftOverall = _curvePlayer.getTimeLeftOverall();
                _currentCurve = _curvePlayer.getCurrentCurveName();
            }
        }
        if (_recording) {
            _recordedTemperature.push_back(_currentTemperature.get());
            _recordedSetpoint.push_back(_setpoint.get());
        }

        calculatePIDOutput();
        _redisHandler.store();
    }
}

void ProcessControl::initSPI() const {
    if (wiringPiSPISetup (0, 1000000) < 0) {
        LOG_ERROR << "SPI Setup failed: %s\n", strerror (errno);
    }
}

void ProcessControl::configureMax31865() const {
    unsigned char msg[] = {0x80, 0xD0};
    wiringPiSPIDataRW (0, msg, 2);
}

void ProcessControl::readTemperature() {
    int val;
    unsigned char recv[50];
    recv[0] = 0x01;
    recv[1] = 0x00;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    wiringPiSPIDataRW (0, recv, 2);
    val = recv[1];
    std::cout << "address 01h: " << int(recv[1]) << std::endl;
    val = val << 8;
    recv[0] = 0x02;
    recv[1] = 0x00;
    std::this_thread::sleep_for(std::chrono::milliseconds(500));
    wiringPiSPIDataRW (0, recv, 2);
    std::cout << "address 02h: " << int(recv[1]) << std::endl;
    val += recv[1];
    std::cout << "val: " << val << std::endl;
    _resistance = (double)(val) / 32768 * 430.0;
    _currentTemperature = ((_resistance.get() / 100) - 1) / 0.00385;
}

void ProcessControl::processCommands() {
    LOG_DEBUG << "Processing commands\n";
    for (const auto& command: _commandAdapter->getCommands()) {
        LOG_DEBUG << "Processing command\n";
        command->execute(*this);
    }
}

void ProcessControl::startRecording() {
    /* _recordingStartTime = std::time(0);
    _recording = true; */
}

void ProcessControl::stopRecording() {
    /* _recording = false;
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
    _recordedSetpoint.clear(); */
}

void ProcessControl::calculatePIDOutput() {
    if (_setpoint.get() < 20) {
        _outputPercent = 0;
    } else {
        _outputPercent = (int)(std::max(std::min((float)100.0, (float)(PROPORTIONAL * (_setpoint.get() - _currentTemperature.get()) / _setpoint.get() * 100)), float(0.0)));
    }
}
