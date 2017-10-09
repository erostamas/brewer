#pragma once

#include <vector>
#include <string>

class ProcessVariableBase;

class ProcessVariableStore {
public:
    static void add(ProcessVariableBase* var);
    static const std::vector<ProcessVariableBase*>& getVariables();
    static void remove(const std::string& name);

public:
    static std::vector<ProcessVariableBase*> _variables;
};
