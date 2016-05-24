#pragma once
#include <vector>
#include <map>
#include <string>

#include "Segment.h"
#include "Common.h"

class CurveStore {

public:
    CurveStore();
    ~CurveStore();
    void addCurve(std::string name, Curve curve);
    Curve getCurve(std::string name);
    unsigned int getSize();

    Curves _curves;
};