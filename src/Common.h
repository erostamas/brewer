#pragma once

#include <vector>
#include <map>
#include <sys/stat.h>
#include <memory>

#include "Segment.h"

class ProcessControl;

extern bool stopControlRequested;
extern ProcessControl processcontrol;

typedef std::shared_ptr<Segment> SegmentPtr;
typedef std::vector<SegmentPtr> Curve;

typedef std::shared_ptr<Curve> CurvePtr;
typedef std::map<std::string, CurvePtr> Curves;