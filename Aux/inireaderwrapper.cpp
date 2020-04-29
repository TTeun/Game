//
// Created by pc on 4/29/20.
//

#include "inireaderwrapper.h"

IniReaderWrapper::IniReaderWrapper(const char *path)
        : m_reader(path) {
    if (m_reader.ParseError() == -1) {
        throw std::string("could not read ") + path + "\n";
    }

}
