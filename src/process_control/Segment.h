#pragma once

#include <string>
#include <memory>

#include "Common.h"

class Segment {
public:
    Segment(const std::string& segmentString);

    double getSetpoint()const ;
    unsigned long getDuration() const;
    std::string toString() const;

private:
    double _setpoint = 0.0;
    Seconds _duration = 0.0;
};

typedef std::shared_ptr<Segment> SegmentPtr;
