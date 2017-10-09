#include "ProcessVariableBase.h"
#include "ProcessVariableStore.h"

std::string toString(MODE mode) {
    switch (mode) {
        case MODE::MANUAL :
            return "MANUAL";
        case MODE::AUTO :
            return "AUTO";
        default:
            return "";
    }
}

ProcessVariableBase::ProcessVariableBase(const std::string& name, Accessibility accessibility)
    : _name(name)
    , _accessibility(accessibility) {
    ProcessVariableStore::add(this);
}

ProcessVariableBase::~ProcessVariableBase() {
    ProcessVariableStore::remove(_name);
}