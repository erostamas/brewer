#pragma once

class Segment {
public:
    Segment() {};
    Segment(double setpoint, unsigned long duration) : _setpoint(setpoint), _duration(duration) {}
    double getSetpoint() { return _setpoint; }
    double getDuration() { return _duration; }
    void setSetpoint(double setpoint) { _setpoint = setpoint; }
    void setDuration(unsigned long duration) { _duration = duration; }
    std::string toString() { return std::to_string(_setpoint) + ":" + std::to_string(_duration); }
private:
    double _setpoint;
    double _duration;
};