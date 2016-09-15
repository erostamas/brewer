#include <sstream>
#include <iomanip>

#include "Segment.h"

Segment::Segment() {
}

Segment::Segment(double setpoint, unsigned long duration) : _setpoint(setpoint), _duration(duration) {
}

double Segment::getSetpoint() {
    return _setpoint;
}

unsigned long Segment::getDuration() {
    return _duration;
}

void Segment::setSetpoint(double setpoint) {
    _setpoint = setpoint;
}

void Segment::setDuration(unsigned long duration) {
    _duration = duration;
}

std::string Segment::toString() {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << _setpoint << ":" << _duration;
    return ss.str();
}
