#pragma once

#include <vector>
#include <map>
#include <sys/stat.h>
#include <memory>

#include "Segment.h"

class ProcessControl;

extern bool stopControlRequested;
extern ProcessControl processcontrol;

typedef std::vector<std::shared_ptr<Segment>> Curve;
typedef std::map<std::string, Curve> Curves;