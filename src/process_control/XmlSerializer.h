#pragma once

#include <string>
#include <sstream>

#include "ISerializer.h"

class XmlSerializer : public ISerializer {
public:
    XmlSerializer();
    XmlSerializer(const std::string& filePath);

    virtual void serialize() const override;
    virtual void serialize(std::stringstream& ss) const override;

private:
    std::string _filePath;
};