//
// Created by pc on 4/29/20.
//

#include "inireaderwrapper.h"

#include <iostream>
#include <limits>

IniReaderWrapper::IniReaderWrapper(const std::string path) : m_reader(path), m_path(path)
{
    if (m_reader.ParseError() == -1) {
        throw std::string("could not read ") + path + "\n";
    }
}

float IniReaderWrapper::getReal(const std::string & section, const std::string & name, float defaultValue) const
{
    const double foundValue = m_reader.GetReal(section, name, std::numeric_limits<double>::max());
    if (foundValue == std::numeric_limits<double>::max()) {
        std::cout << "Could not read " << name << " from the file " << m_path << '\n';
        return defaultValue;
    }
    std::cout << name << ": " << foundValue << '\n';
    return static_cast<float>(foundValue);
}
