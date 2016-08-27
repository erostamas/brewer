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

void CurveStore::addCurve(std::string name, CurvePtr curve) {
    _curves[name] = curve;
}

bool CurveStore::addCurve(std::string name, std::string curve_string) {
    LOG_DEBUG << "Trying to parse curve from string: " << name << ": " << curve_string;
    const std::vector<std::string> segments = Utils::split(curve_string, ';');
    if (!segments.size()) { return false; }
    CurvePtr curve(new Curve());
    int segment_counter = 0;
    for (auto&& segment : segments ) {
        segment_counter++;
        std::vector<std::string> values = Utils::split(segment, ':');
        if (values.size() != 2) {
            LOG_ERROR << "Segment number " << segment_counter << " malformed in " << name << ": " << curve_string;
            return false;
        }
        if (values.size() == 2) {
            double setpoint = 0;
            unsigned long duration = 0;
            try {
                setpoint = std::stod(values[0]);
                LOG_DEBUG << "Segment parsed with setpoint: " << setpoint;
            } catch (...) {
                LOG_ERROR << "Exception during parsing setpoint in segment number " << segment_counter;
                return false;
            }
            try {
                duration = std::stoul(values[1]);
                LOG_DEBUG << "Segment parsed with duration: " << duration;
            } catch (...) {
                LOG_ERROR << "Exception during parsing duration in segment number " << segment_counter;
                return false;
            }
            auto new_segment = std::make_shared<Segment>(setpoint, duration);
            LOG_DEBUG << "Added segment to curve " << name << " - sp: " << setpoint << " dur: " << duration;
            curve->push_back(new_segment);
        }
    }
    addCurve(name, curve);
    return true;
}

CurvePtr CurveStore::getCurve(std::string name) {
    try {
         return _curves.at(name);
    } catch (...) {
        LOG_ERROR << "Exception during getting curve: " << name << ", it probably does not exist";
    }
    return nullptr;
}

unsigned int CurveStore::getSize() {
    return _curves.size();
}

void CurveStore::saveCurvesToFile(std::string curve_file_path) {
    std::ofstream curve_file;
    curve_file.open (curve_file_path);
    for (auto&& curve: _curves) {
        curve_file << curve.first << " ";
        bool first_done = false;
        for (auto&& segment : *curve.second) {
            if (first_done) {
                curve_file << ";";
            }
            curve_file << segment->toString();
            first_done = true;
        }
        curve_file << "\n";
    }
}

void CurveStore::initCurvesFromFile(std::string curve_file_path) {
    if (!Utils::fileExists(curve_file_path)) {
        LOG_ERROR << "Curve file: " << curve_file_path << " does not exist, failed to initialize curves";
        return;
    } else {
        LOG_INFO << "Initializing curves from file: "<< curve_file_path;
        std::ifstream curvefile(curve_file_path);
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