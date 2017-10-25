#pragma once

#include <memory>

#include "CurveStore.h"
#include "ProcessVariable.h"
#include "XmlSerializer.h"
#include "ICommandAdapter.h"
#include "System.h"

class SetpointCommand;
class DeltaSetpointCommand;

class ProcessControl {
public:
    ProcessControl(SystemPtr system = nullptr);
    ~ProcessControl();
	void setSimulationMode(bool simulationMode) { _simulationMode = simulationMode; }

	void run();
    void playCurve(std::string name);
    void stopCurve();
    void processCommands();
    void startRecording();
    void stopRecording();
    void calculatePIDOutput();
    void initSPI() const;
    void configureMax31865() const;
    void readTemperature();
    ProcessVariable<TYPE::DOUBLE>& getSetpoint() { return _setpoint; }

private:
    friend class SetpointCommand;
    friend class DeltaSetpointCommand;
    SystemPtr _system;
    ProcessVariable<TYPE::DOUBLE> _currentTemperature;
    ProcessVariable<TYPE::DOUBLE> _resistance;
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
    std::string _lastCommand;
    XmlSerializer _xmlSerializer;
    std::unique_ptr<ICommandAdapter> _commandAdapter;
    
};