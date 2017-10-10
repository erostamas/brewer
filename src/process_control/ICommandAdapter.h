#pragma once

#include <vector>
#include <memory>

#include "ICommand.h"

class ICommandAdapter {
public:
    virtual std::vector<std::unique_ptr<ICommand>> getCommands() const = 0;
    virtual void startCommandReceiver() = 0;
};