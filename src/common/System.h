#pragma once

#include <chrono>

#include "ISystem.h"

class System : public ISystem {
public:
    virtual Seconds getTsNow() const override {
        using namespace std::chrono;
        return duration_cast<seconds>(system_clock::now().time_since_epoch()).count();
    }
};