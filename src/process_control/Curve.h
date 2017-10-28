#pragma once

#include <string>
#include <vector>

#include "Segment.h"

class Curve {
public:
    Curve(const std::string& name, const std::string& curveString);

    std::size_t size() const     { return _segments.size(); }
    std::string toString() const;
    SegmentPtr getSegment(size_t index) const;
    std::string getName() const { return _name; }

private:
    void parseSegments(const std::string& curveString);

    std::string _name;
    std::vector<SegmentPtr> _segments;
};

using CurvePtr = std::shared_ptr<Curve>;