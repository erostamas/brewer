#pragma once

#include <vector>
#include <map>

#include "Segment.h"
class ProcessControl;

extern bool stopControlRequested;
extern double currentTemperature;
extern double setpoint;
extern ProcessControl processcontrol;

typedef std::vector<Segment> Curve;
typedef std::map<std::string, Curve> Curves;