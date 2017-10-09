#pragma once

#include "CurveStore.h"
#include "UdpInterface.h"
#include "ProcessVariable.h"
#include "XmlSerializer.h"

class ProcessControl {
public:
    ProcessControl();
    ~ProcessControl();
	void setSimulationMode(bool simulationMode)           { _simulationMode = simulationMode;         }

	void run();
    void playCurve(std::string name);
    void stopCurve();
    void processCommands();
    void processCommand(std::string message);
    void startRecording();
    void stopRecording();
    void calculatePIDOutput();

private:
    ProcessVariable<TYPE::DOUBLE> _currentTemperature;
    ProcessVariable<TYPE::DOUBLE> _setpoint;
    ProcessVariable<TYPE::INTEGER> _outputPercent;
    ProcessVariable<TYPE::MODE> _mode;
    bool _simulationMode;
    CurveStore _curveStore;
    std::string _currentCurve;
    unsigned int _currentSegmentIndex;
    SegmentPtr _currentSegment;
    unsigned long _timeToNextSegment;
    std::vector<float> _recordedTemperature;
    std::vector<float> _recordedSetpoint;
    time_t _recordingStartTime;
    bool _recording;
    long _segmentStartTime;
    UdpInterface _udpInterface;
    std::string _lastCommand;
    XmlSerializer _xmlSerializer;
    
};