#pragma once

#include "ICommand.h"

#include "ProcessControl.h"

class SetpointCommand : public ICommand {
public:
    SetpointCommand(double setpoint)
    : _setpoint(setpoint) {
    }

    virtual void execute(ProcessControl& processControl) override {
        processControl.getSetpoint() = _setpoint;
    }

private:
    double _setpoint = 0.0;
};