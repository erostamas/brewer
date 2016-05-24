#pragma once

#include "CurveStore.h"

enum class MODE {
    MANUAL,
    AUTO
};

class ProcessControl {
public:
    ProcessControl();
	void setSimulationMode(bool simulationMode)           { _simulationMode = simulationMode;         }
	
    void initCurves();
	void run();
    void playCurve(std::string name);
    void stopCurve();

private:
    bool _simulationMode;
    MODE _mode;
    CurveStore _curveStore;
    std::string _currentCurve;
    unsigned int _currentSegmentIndex;
};