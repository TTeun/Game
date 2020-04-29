//
// Created by pc on 4/29/20.
//

#ifndef TEUN_GAME_INIREADERWRAPPER_H
#define TEUN_GAME_INIREADERWRAPPER_H

#include "../ThirdParty/inih-master/cpp/INIReader.h"


class IniReaderWrapper {


public:
    explicit IniReaderWrapper(const char *path = "../Config/physics.ini");

    float getReal(const std::string &section, const std::string &name, double defaultValue) const {
        return static_cast<float>( m_reader.GetReal(section, name, defaultValue));
    }

private:
    INIReader m_reader;

};


#endif //TEUN_GAME_INIREADERWRAPPER_H
