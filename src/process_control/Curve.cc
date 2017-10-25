#include <stdexcept>

#include "Curve.h"
#include "Utils.h"

Curve::Curve(const std::string& name, const std::string& segments)
: _name(name) {
    parseSegments(segments);
}

Curve::parseSegments(const std::string& segmentStrings) {
    const std::vector<std::string> segments = Utils::split(curve_string, ';');
    if (segments.empty()) {
        throw CurveParseError("[Curve] Failed parsing curve from string: " + segmentsString);
    }
    for (auto&& segmentString : segmentStrings) {
        _segments.emplace_back(new Segment(segmentString));
    }
}