#pragma once

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <sstream>

namespace pt = boost::property_tree;
using PropertyTree = pt::ptree;

class Config {
    static constexpr const char* CONFIG_PATH = "/brewer_files/config.json";

public:
    Config();
    explicit Config(std::istringstream& config);
    
    int getInteger(const std::string& path);
    std::string getString(const std::string& path);
    template<class ValueType>
    ValueType getInteger(const std::string& path, ValueType defaultValue);
    PropertyTree& getCompound(const std::string& path);

private:
    PropertyTree _root;

};

template<class ValueType>
ValueType Config::getInteger(const std::string& path, ValueType defaultValue) {
    return _root.get(path, defaultValue);
}