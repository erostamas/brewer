#pragma once

class Segment {
public:
    Segment();
    Segment(double setpoint, double duration) : _setpoint(setpoint), _duration(duration) {}
    double getSetpoint() { return _setpoint; }
    double getDuration() { return _duration; }
    
    void setSetpoint(double setpoint) { _setpoint = setpoint; }
    void setDuration(double duration) { _duration = duration; }
private:
    double _setpoint;
    double _duration;
};