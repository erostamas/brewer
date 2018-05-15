#pragma once

#include "ICommand.h"
#include "ProcessControl.h"
#include "Exceptions.h"

class ShutdownCommand : public ICommand {
public:
    ShutdownCommand() = default;

    virtual void execute(ProcessControl& processControl) override {
        throw NormalShutdown();
    }
};