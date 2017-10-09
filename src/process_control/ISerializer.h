#pragma once

#include "ProcessVariableStore.h"

class ISerializer {
public:
    virtual void serialize() const = 0;
    virtual void serialize(std::stringstream& ss) const = 0;

};