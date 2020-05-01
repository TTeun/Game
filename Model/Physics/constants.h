//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_CONSTANTS_H
#define TEUN_GAME_CONSTANTS_H

#include "../../Aux/inireaderwrapper.h"

#include <memory>

namespace Model {

    namespace Physics {

        struct Constants {

        public:
            static std::unique_ptr<Constants> create(std::string path = "../Config/physics.ini");

        private:
            explicit Constants(std::string path = "../Config/physics.ini");

            std::unique_ptr<IniReaderWrapper> m_iniReader;

        public:
            const float m_gravitationalConstant;
            const float m_surfaceFriction;
            const float m_jumpVelocity;
            const float m_wallJumpYVelocity;
            const float m_wallJumpXVelocity;
            const float m_maxHorizontalSpeed;
            const float m_maxVerticalSpeed;
        };
    } // namespace Physics
} // namespace Model

#endif // TEUN_GAME_CONSTANTS_H
