//
// Created by pc on 4/29/20.
//

#ifndef TEUN_GAME_INIREADERWRAPPER_H
#define TEUN_GAME_INIREADERWRAPPER_H

#include "../ThirdParty/inih-master/cpp/INIReader.h"


class IniReaderWrapper {


public:
    explicit IniReaderWrapper(std::string path = "../Config/physics.ini");

    float getReal(const std::string &section, const std::string &name, float defaultValue) const;

private:
    INIReader m_reader;
    std::string m_path;


};


#endif //TEUN_GAME_INIREADERWRAPPER_H
