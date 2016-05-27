#include <iostream>
#include <fstream>

#include "CurveStore.h"
#include "Utils.h"

CurveStore::CurveStore() {
    
}

CurveStore::~CurveStore() {

}

void CurveStore::addCurve(std::string name, Curve curve) {
    _curves[name] = curve;
}

bool CurveStore::addCurve(std::string name, std::string curve_str) {
    const std::vector<std::string> segments = Utils::split(curve_str, ';');
    if (!segments.size()) { return false; }
    Curve curve;
    for (auto&& segment : segments ) {
        std::vector<std::string> values = Utils::split(segment, ':');
        if (values.size() > 0 && values.size() < 3) {
            double setpoint = 0;
            unsigned long duration = 0;
            try {
                setpoint = std::stod(values[0]);
            } catch (...) {
                std::cout << "Exception during segment parsing" << std::endl;
                return false;
            }
            if (values.size() == 2) {
                try {
                    duration = std::stoul(values[1]);
                } catch (...) {
                    std::cout << "Exception during segment parsing" << std::endl;
                    return false;
                }
            }
            Segment* new_segment = new Segment(setpoint, duration);
            curve.push_back(new_segment);
        }
    }
    addCurve(name, curve);
    return true;
}

Curve CurveStore::getCurve(std::string name) {
    Curve curve;
    try {
         curve = _curves.at(name);
    } catch (...) {
        std::cout << "Exception during getting curve: " << name << ", it probably does not exist" << std::endl;
    }
    return curve;
}

unsigned int CurveStore::getSize() {
    return _curves.size();
}

void CurveStore::saveCurves() {
    std::ofstream curve_file;
    curve_file.open ("/brewer_files/brewer_curves.txt");
    for (auto&& curve: _curves) {
        curve_file << curve.first << " ";
        bool first_done = false;
        for (auto&& segment : curve.second) {
            if (first_done) {
                curve_file << ";";
            }
            curve_file << segment->toString();
            first_done = true;
            delete segment;
        }
    }
}