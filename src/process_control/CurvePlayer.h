#pragma once

#include <memory>

#include "System.h"
#include "Curve.h"

enum class CurvePlayerState : uint8_t {
    IDLE = 0
  , RUNNING = 1
  , PAUSED = 2
};

class CurvePlayer {
public:
    CurvePlayer(SystemPtr system = nullptr);

    double getCurrentSetpoint() const { return _currentSetpoint; }
    CurvePlayerState getState() const { return _state;           }
    Seconds getTimeToNextSegment() const { return _timeToNextSegment; }
    Seconds getTimeLeftOverall() const { return _timeLeftOverall; }
    std::string getCurrentCurveName() const { return _currentCurveName; }
    void playCurve(CurvePtr curve);
    void step();
    void stop();
    void pause();
    void resume();
    void reset();

private:
    SystemPtr _system;
    CurvePlayerState _state = CurvePlayerState::IDLE;
    CurvePtr _curve = nullptr;
    size_t _currentSegmentIndex = 0;
    SegmentPtr _currentSegment;
    MilliSeconds _nextStep;
    MilliSeconds _endTime;
    double _currentSetpoint;
    Seconds _timeToNextSegment;
    Seconds _timeLeftOverall;
    std::string _currentCurveName;
};