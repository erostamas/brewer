#pragma once

#include "ICommand.h"

class ProcessControl;

class DeltaSetpointCommand : public ICommand {
public:
    DeltaSetpointCommand(double delta)
    : _delta(delta) {
    }

    virtual void execute(ProcessControl& processControl) override {
        processControl.getSetpoint() = processControl.getSetpoint().get() + _delta;
    }

private:
    double _delta = 1.0;
};