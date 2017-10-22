#pragma once

#include <stdexcept>

struct NormalShutdown : public std::exception {
    NormalShutdown() = default;
    const char* what() const throw() {return "Shutdown requested by UI";}
};