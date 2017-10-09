#include "ProcessVariableStore.h"

#include "ProcessVariableBase.h"

std::vector<ProcessVariableBase*> ProcessVariableStore::_variables;

void ProcessVariableStore::add(ProcessVariableBase* var) {
    _variables.push_back(var);
}

const std::vector<ProcessVariableBase*>& ProcessVariableStore::getVariables() {
    return _variables;
}

void ProcessVariableStore::remove(const std::string& name) {
    for (auto it = _variables.begin(); it != _variables.end(); ) {
        if ((*it)->getName() == name) {
            it = _variables.erase(it);
        } else {
            ++it;
        }
    }
}