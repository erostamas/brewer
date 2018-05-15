#pragma once

#include "ICommand.h"

class ProcessControl;

class PauseCurveCommand : public ICommand {
public:
    PauseCurveCommand() {}

    virtual void execute(ProcessControl& processControl) override {
        processControl._curvePlayer.pause();
    }
};