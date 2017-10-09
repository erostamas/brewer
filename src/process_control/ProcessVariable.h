#pragma once

#include <string>
#include <iostream>

#include "ProcessVariableBase.h"

template<TYPE Type>
class ProcessVariable : public ProcessVariableBase {
public:
    typedef typename enum_to_type<Type>::type BaseType;

    ProcessVariable(const std::string& name, Accessibility accessibility)
        : ProcessVariableBase(name, accessibility) {
        _type = Type;
    }

    BaseType get() const {
        return _value;
    }

    void operator=(const BaseType& rhs) {
        _value = rhs;
    }

    bool operator==(const BaseType& rhs) {
        return _value == rhs;
    }

private:
    BaseType _value = BaseType();
};

template<TYPE Type>
std::ostream& operator<<(std::ostream& os, const ProcessVariable<Type>& var)  
{  
    os << var.get();  
    return os;  
}  