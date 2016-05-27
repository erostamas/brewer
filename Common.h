#pragma once

#include <vector>
#include <map>
#include <sys/stat.h>

#include "Segment.h"

class ProcessControl;

extern bool stopControlRequested;
extern ProcessControl processcontrol;

typedef std::vector<Segment*> Curve;
typedef std::map<std::string, Curve> Curves;