#pragma once

#include <memory>

using MicroSeconds = uint64_t;
using MilliSeconds = uint64_t;
using Seconds = uint64_t;

class ISystem {
public:
    virtual MilliSeconds getTsNow() const = 0;
};

using SystemPtr = std::shared_ptr<ISystem>;