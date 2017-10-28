#pragma once

#include <chrono>

#include "ISystem.h"

class FakeSystem : public ISystem {
public:
    virtual Seconds getTsNow() const override {
        return _tsNow;
    }

    void sleep(Seconds sleep) {
        _tsNow += sleep;
    }

private:
    Seconds _tsNow = 0;
};