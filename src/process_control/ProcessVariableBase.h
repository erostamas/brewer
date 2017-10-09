#pragma once

#include <string>

enum class TYPE : uint8_t {
    DOUBLE = 0
  , INTEGER = 1
  , STRING = 2
  , MODE = 3
};

enum class MODE : uint8_t {
    MANUAL = 0
  , AUTO = 1
};

std::string toString(MODE mode);

template<TYPE T> struct enum_to_type            {static_assert(true, "Invalid type");};
template<> struct enum_to_type<TYPE::DOUBLE>    {typedef double type;     };
template<> struct enum_to_type<TYPE::INTEGER>   {typedef int type;     };
template<> struct enum_to_type<TYPE::STRING>    {typedef std::string type;};
template<> struct enum_to_type<TYPE::MODE>      {typedef MODE type;};

enum class Accessibility : uint8_t {
    READONLY = 0
  , READWRITE = 1
};

class ProcessVariableBase {
public:
    ProcessVariableBase(const std::string& name, Accessibility accessibility);
    ~ProcessVariableBase();

    TYPE getType() const { return _type; }
    std::string getName() const { return _name; }

protected:
    std::string _name;
    Accessibility _accessibility;
    TYPE _type = TYPE::DOUBLE;
};