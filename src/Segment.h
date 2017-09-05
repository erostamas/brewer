#pragma once

#include <string>
#include <memory>
#include <vector>
#include <map>

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

typedef std::shared_ptr<Segment> SegmentPtr;
typedef std::vector<SegmentPtr> Curve;
typedef std::shared_ptr<Curve> CurvePtr;
typedef std::map<std::string, CurvePtr> Curves;