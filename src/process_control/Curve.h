#pragma once

#include <string>

class Curve {
public:
    Curve(const std::string& name, const std::string& segments);

private:
    void parseSegments(const std::string& segmentsString);

    std::string _name;
    std::vector<SegmentPtr> _segments;
};