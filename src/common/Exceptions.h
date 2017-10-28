#pragma once

#include <stdexcept>

struct NormalShutdown : public std::exception {
    NormalShutdown() = default;
    const char* what() const throw() {return "Shutdown requested by UI";}
};

struct CurveParseError : public std::runtime_error {
    CurveParseError(const std::string& msg)
    : std::runtime_error(msg)
    {}
};

struct SegmentParseError : public std::runtime_error {
    SegmentParseError(const std::string& msg)
    : std::runtime_error(msg)
    {}
};