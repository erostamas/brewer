#pragma once

#include "CurveStore.h"
#include "UnixDomainSocketInterface.h"

enum class MODE {
    MANUAL,
    AUTO
};

class ProcessControl {
public:
    ProcessControl(UnixDomainSocketInterface*);
    ~ProcessControl();
	void setSimulationMode(bool simulationMode)           { _simulationMode = simulationMode;         }

	void run();
    void playCurve(std::string name);
    void stopCurve();
    void processCommands();
    void processCommand(std::string message);
    void writeXML();
    void printState();
    void startRecording();
    void stopRecording();
    void calculatePIDOutput();

private:
    bool _simulationMode;
    MODE _mode;
    CurveStore _curveStore;
    std::string _currentCurve;
    unsigned int _currentSegmentIndex;
    UnixDomainSocketInterface* _unixInterface;
    float _currentTemperature = 0;
    float _setpoint = 0;
    SegmentPtr _currentSegment;
    unsigned long _timeToNextSegment;
    std::vector<float> _recordedTemperature;
    std::vector<float> _recordedSetpoint;
    time_t _recordingStartTime;
    bool _recording;
    long _segmentStartTime;
    unsigned _outputPercent = 0;
    
};