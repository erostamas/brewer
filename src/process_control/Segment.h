#pragma once

#include <string>
#include <memory>

#include "Common.h"

class Segment {
public:
    Segment(const std::string& segmentString);

    double getSetpoint();
    unsigned long getDuration();
    std::string toString();

private:
    double _setpoint = 0.0;
    Seconds _duration = 0.0;
};

typedef std::unique_ptr<Segment> SegmentPtr;
