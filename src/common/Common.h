#pragma once

#include <vector>
#include <map>
#include <sys/stat.h>
#include <memory>

class ProcessControl;

extern bool stopControlRequested;
extern ProcessControl processcontrol;

using MicroSeconds = uint64_t;
using MilliSeconds = uint64_t;
using Seconds = uint64_t;

struct CurveParseError : public std::runtime_error {
    CurveParseError(const std::string& msg)
    : std::runtime_error(msg)
    {}
};

struct SegmentParseError : public std::runtime_error {
    SegmentParseError(const std::string& msg)
    : std::runtime_error(msg)
    {}
};
