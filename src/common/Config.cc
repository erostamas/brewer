#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/detail/json_parser_error.hpp>

#include "Config.h"

Config::Config() {
    pt::read_json(CONFIG_PATH, _root);
}

Config::Config(std::istringstream& config) {
    pt::read_json(config, _root);
}

int Config::getInteger(const std::string& path) {
    return _root.get<int>(path);
}

std::string Config::getString(const std::string& path) {
    return _root.get<std::string>(path);
}

PropertyTree& Config::getCompound(const std::string& path) {
    return _root.get_child(path);
}