#include <sstream>
#include <iomanip>

#include "Segment.h"
#include "Common.h"
#include "Utils.h"
#include "Exceptions.h"

Segment::Segment(const std::string& segmentString) {
    std::vector<std::string> values = Utils::split(segmentString, ':');
    if (values.size() != 2) {
        throw SegmentParseError("[Segment] Malformed segment: " + segmentString);
    }
    try {
        _setpoint = std::stod(values[0]);
    } catch (...) {
        throw SegmentParseError("[Segment] Failed to parse setpoint: " + values[0]);
    }
    try {
        _duration = std::stoul(values[1]);
    } catch (...) {
        throw SegmentParseError("[Segment] Failed to parse duration: " + values[1]);
    }
}

double Segment::getSetpoint() const {
    return _setpoint;
}

unsigned long Segment::getDuration() const {
    return _duration;
}

std::string Segment::toString() const {
    std::stringstream ss;
    ss << std::fixed << std::setprecision(2) << _setpoint << ":" << _duration;
    return ss.str();
}
