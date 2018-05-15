#pragma once

#include "ICommand.h"

class ProcessControl;

class PlayCurveCommand : public ICommand {
public:
    PlayCurveCommand(CurvePtr curve)
    : _curve(curve) {
    }

    virtual void execute(ProcessControl& processControl) override {
        processControl._mode = MODE::AUTO;
        processControl._curvePlayer.playCurve(_curve);
    }

private:
    CurvePtr _curve = nullptr;
};