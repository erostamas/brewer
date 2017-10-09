#pragma once

class ICommandAdapter {
public:
    Commands getCommands() const = 0;
};