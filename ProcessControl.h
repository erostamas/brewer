#pragma once

#include "CurveStore.h"
#include "TcpInterface.h"

enum class MODE {
    MANUAL,
    AUTO
};

class ProcessControl {
public:
    ProcessControl(TcpInterface*);
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

private:
    bool _simulationMode;
    MODE _mode;
    CurveStore _curveStore;
    std::string _currentCurve;
    unsigned int _currentSegmentIndex;
    TcpInterface* _tcpInterface;
    float _currentTemperature;
    float _setpoint;
    std::shared_ptr<Segment> _currentSegment;
    unsigned long _timeToNextSegment;
    std::vector<float> _recordedTemperature;
    std::vector<float> _recordedSetpoint;
    time_t _recordingStartTime;
    bool _recording;
    long _segmentStartTime;
    
};