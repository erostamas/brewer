#pragma once

#include <boost/property_tree/ptree.hpp>
#include <string>
#include <sstream>

#include "Logging.h"

namespace pt = boost::property_tree;
using PropertyTree = pt::ptree;

class Config {
    static constexpr const char* CONFIG_PATH = "/opt/erostamas/brewer/config.json";

public:
    Config();
    explicit Config(std::istringstream& config);

    template<class ValueType>
    ValueType get(const std::string& path, ValueType defaultValue) {
        ValueType value = _root.get(path, defaultValue);
        LOG_INFO << "[Config] " << path << " : " << value;
        return value;
    }
    PropertyTree& getCompound(const std::string& path);

private:
    PropertyTree _root;

};
