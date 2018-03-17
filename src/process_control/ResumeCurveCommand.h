#pragma once

#include "ICommand.h"

class ProcessControl;

class ResumeCurveCommand : public ICommand {
public:
    ResumeCurveCommand() {}

    virtual void execute(ProcessControl& processControl) override {
        processControl._curvePlayer.resume();
    }
};