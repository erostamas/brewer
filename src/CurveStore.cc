#include <boost/log/trivial.hpp>
#include <iostream>
#include <fstream>

#include "CurveStore.h"
#include "Logging.h"
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
                LOG_DEBUG << "Segment parsed with setpoint: " << setpoint;
            } catch (...) {
                LOG_ERROR << "Exception during segment parsing";
                return false;
            }
            if (values.size() == 2) {
                try {
                    duration = std::stoul(values[1]);
                    LOG_DEBUG << "Segment parsed with duration: " << duration;
                } catch (...) {
                    LOG_ERROR << "Exception during segment parsing";
                    return false;
                }
            }
            auto new_segment = std::make_shared<Segment>(setpoint, duration);
            LOG_DEBUG << "Added segment to curve " << name << " - sp: " << setpoint << " dur: " << duration;
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
        LOG_ERROR << "Exception during getting curve: " << name << ", it probably does not exist";
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
        }
        curve_file << "\n";
    }
}

void CurveStore::initCurves() {
    if (!Utils::fileExists("/brewer_files/brewer_curves.txt")) {
        return;
    } else {
        std::ifstream curvefile("/brewer_files/brewer_curves.txt");
        std::string line;
        while (std::getline(curvefile, line))
        {
            const std::vector<std::string> v = Utils::split(line, ' ');
            if (v.size() != 2) {
                LOG_ERROR << "Error in curve definition";
            } else {
                if(addCurve(v[0], v[1])) {
                    LOG_INFO << "Successfully initialized curve: " << v[0];
                }
            }
        }
    }
}

std::string CurveStore::getCurveNames() {
    std::string ret = "";
    for (auto&& curve : _curves) {
        if (ret != "") {
            ret.append(";");
        } else {
            ret.append("curves: ");
        }
        ret.append(curve.first);
    }
    return ret;
}