#pragma once

#include "ICommand.h"

#include "ProcessControl.h"

class SetpointCommand : public ICommand {
public:
    SetpointCommand(double setpoint)
    : _setpoint(setpoint) {
    }

    virtual void execute(ProcessControl& processControl) override {
        processControl._mode = MODE::MANUAL;
        processControl._curvePlayer.stop();
        processControl._setpoint = _setpoint;
    }

private:
    double _setpoint = 0.0;
};