#pragma once

#include <memory>

#include "System.h"
#include "Segment.h"

class CurvePlayer {
public:
    CurvePlayer(SystemPtr system = nullptr);

    void setCurve(CurvePtr curve);
    void step();
    void start();
    void stop();
    void reset();

private:
    SystemPtr _system;
    CurvePtr
};