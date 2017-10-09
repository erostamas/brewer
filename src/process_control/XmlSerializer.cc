#include "XmlSerializer.h"

#include <fstream>

#include "ProcessVariable.h"
#include <iostream>

XmlSerializer::XmlSerializer() {
}

XmlSerializer::XmlSerializer(const std::string& filePath)
    : _filePath(filePath){
}

void XmlSerializer::serialize() const {
    std::ofstream xmlfile;
    xmlfile.open (_filePath);
    std::stringstream ss;
    serialize(ss);
    xmlfile << ss.str();
}

void XmlSerializer::serialize(std::stringstream& ss) const {\
    ss << "<?xml version=\"1.0\"?>\n";
    ss << "<processdata>\n";
    for (auto var : ProcessVariableStore::getVariables()) {
        ss << "<" << var->getName() << ">";
        switch (var->getType()) {
            case TYPE::DOUBLE :
                ss << std::to_string(static_cast<ProcessVariable<TYPE::DOUBLE>*>(var)->get());
                break;
            case TYPE::INTEGER :
                ss << std::to_string(static_cast<ProcessVariable<TYPE::INTEGER>*>(var)->get());
                break;
            case TYPE::STRING :
                ss << static_cast<ProcessVariable<TYPE::STRING>*>(var)->get();
                break;
            case TYPE::MODE :
                ss << toString(static_cast<ProcessVariable<TYPE::MODE>*>(var)->get());
        }
        ss << "</" << var->getName() << ">\n";
    }
    ss << "</processdata>\n";
}