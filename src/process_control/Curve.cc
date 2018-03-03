#include <sstream>

#include "Curve.h"
#include "Utils.h"
#include "Exceptions.h"

Curve::Curve(const std::string& name, const std::string& curveString)
: _name(name) {
    parseSegments(curveString);
}

void Curve::parseSegments(const std::string& curveString) {
    const std::vector<std::string> segmentStrings = Utils::split(curveString, ';');
    if (segmentStrings.empty()) {
        throw CurveParseError("[Curve] Failed parsing curve from string: " + curveString);
    }
    for (auto&& segmentString : segmentStrings) {
        SegmentPtr newSegment = std::make_shared<Segment>(segmentString);
        _duration += newSegment->getDuration();
        _segments.push_back(newSegment);
    }
}

std::string Curve::toString() const {
    std::stringstream ss;
    for (unsigned i = 0; i < size(); i++) {
        ss << _segments[i]->toString();
        if (i != size() - 1) {
            ss << ";";
        }
    }
    return ss.str();
}

SegmentPtr Curve::getSegment(size_t index) const {
    if (index < size()) {
        return _segments[index];
    } else {
        return nullptr;
    }
}