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
    bool addCurve(std::string name, std::string curve_str);
    Curve getCurve(std::string name);
    void saveCurves();
    unsigned int getSize();

    Curves _curves;
};