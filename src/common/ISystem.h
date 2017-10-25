#pragma once

#include <memory>

#include "Common.h"

class ISystem {
public:
    virtual MilliSeconds getTsNow() const = 0;
};

using SystemPtr = std::shared_ptr<ISystem>;