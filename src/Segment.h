#pragma once
#include <string>

class Segment {
public:
    Segment();
    Segment(double setpoint, unsigned long duration);
    double getSetpoint();
    unsigned long getDuration();
    void setSetpoint(double setpoint);
    void setDuration(unsigned long duration);
    std::string toString();
private:
    double _setpoint = 0.0;
    unsigned long _duration = 0.0;
};