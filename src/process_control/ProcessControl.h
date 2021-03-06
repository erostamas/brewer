#pragma once

#include <memory>

#include "ProcessVariable.h"
#include "ICommandAdapter.h"
#include "System.h"
#include "CurvePlayer.h"
#include "RedisHandler.h"

class SetpointCommand;
class DeltaSetpointCommand;
class PlayCurveCommand;

class ProcessControl {
public:
    ProcessControl(SystemPtr system = nullptr);
    ~ProcessControl();
	void setSimulationMode(bool simulationMode) { _simulationMode = simulationMode; }

	void run();
    void stopCurve();
    void processCommands();
    void startRecording();
    void stopRecording();
    void calculatePIDOutput();
    void initSPI() const;
    void configureMax31865() const;
    void readTemperature();
    ProcessVariable<TYPE::INTEGER>& getSetpoint() { return _setpoint; }

private:
    friend class SetpointCommand;
    friend class DeltaSetpointCommand;
    friend class PlayCurveCommand;
    friend class PauseCurveCommand;
    friend class ResumeCurveCommand;
    SystemPtr _system;
    ProcessVariable<TYPE::DOUBLE> _currentTemperature;
    ProcessVariable<TYPE::DOUBLE> _resistance;
    ProcessVariable<TYPE::INTEGER> _setpoint;
    ProcessVariable<TYPE::INTEGER> _outputPercent;
    ProcessVariable<TYPE::MODE> _mode;
    ProcessVariable<TYPE::INTEGER> _timeToNextSegment;
    ProcessVariable<TYPE::INTEGER> _timeLeftOverall;
    ProcessVariable<TYPE::STRING> _currentCurve;
    bool _simulationMode;
    std::vector<float> _recordedTemperature;
    std::vector<float> _recordedSetpoint;
    time_t _recordingStartTime;
    bool _recording;
    std::unique_ptr<ICommandAdapter> _commandAdapter;
    CurvePlayer _curvePlayer;
    RedisHandler _redisHandler;
    
};