#include <iostream>

#include "CurveStore.h"

CurveStore::CurveStore() {
    
}

CurveStore::~CurveStore() {
    
}

void CurveStore::addCurve(std::string name, Curve curve) {
    _curves[name] = curve;
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