#pragma once

class ProcessControl;
class ICommand {
public:
    virtual void execute(ProcessControl& processControl) = 0;
};