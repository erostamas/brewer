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
	
    void initCurves();
	void run();
    void playCurve(std::string name);
    void stopCurve();
    void processCommands();
    void processCommand(std::string message);
    void writeXML();
    void printState();

private:
    bool _simulationMode;
    MODE _mode;
    CurveStore _curveStore;
    std::string _currentCurve;
    unsigned int _currentSegmentIndex;
    TcpInterface* _tcpInterface;
    double _currentTemperature;
    double _setpoint;
    Segment* _currentSegment;
    unsigned long _timeToNextSegment;
};