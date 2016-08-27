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
    void addCurve(std::string name, CurvePtr curve);
    bool addCurve(std::string name, std::string curve_str);
    CurvePtr getCurve(std::string name);
    std::string getCurveNames();
    void initCurvesFromFile(std::string path);
    void saveCurvesToFile(std::string path);
    unsigned int getSize();

    Curves _curves;
};