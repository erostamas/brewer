#pragma once

#include <memory>

#include "System.h"
#include "Curve.h"

enum class CurvePlayerState : uint8_t {
    IDLE = 0
  , RUNNING = 1
};

class CurvePlayer {
public:
    CurvePlayer(SystemPtr system = nullptr);

    double getCurrentSetpoint() const { return _currentSetpoint; }
    CurvePlayerState getState() const { return _state;           }
    Seconds getTimeToNextSegment() const { return _timeToNextSegment; }
    void playCurve(CurvePtr curve);
    void step();
    void stop();
    void reset();

private:
    SystemPtr _system;
    CurvePlayerState _state = CurvePlayerState::IDLE;
    CurvePtr _curve = nullptr;
    size_t _currentSegmentIndex = 0;
    SegmentPtr _currentSegment;
    MilliSeconds _nextStep;
    double _currentSetpoint;
    Seconds _timeToNextSegment;
};