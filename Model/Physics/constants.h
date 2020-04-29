//
// Created by pc on 4/26/20.
//

#ifndef TEUN_GAME_CONSTANTS_H
#define TEUN_GAME_CONSTANTS_H

#include <memory>
#include "../Entities/level.h"

#include "../../ThirdParty/inih-master/cpp/INIReader.h"
#include "../../Aux/inireaderwrapper.h"

namespace Model {

    namespace Physics {

        struct Constants {

//            Constants(const float gravitationalConstant, const float surfaceFriction, const float jumpVelocity,
//                      const float wallJumpYVelocity, const float wallJumpXVelocity, const float maxHorizontalSpeed,
//                      const float maxVerticalSpeed) : m_gravitationalConstant(gravitationalConstant),
//                                                      m_surfaceFriction(surfaceFriction), m_jumpVelocity(jumpVelocity),
//                                                      m_wallJumpYVelocity(wallJumpYVelocity),
//                                                      m_wallJumpXVelocity(wallJumpXVelocity),
//                                                      m_maxHorizontalSpeed(maxHorizontalSpeed),
//                                                      m_maxVerticalSpeed(maxVerticalSpeed) {}


            explicit Constants(const char *path = "../Config/physics.ini")
                    : m_iniReader(std::make_unique<IniReaderWrapper>(IniReaderWrapper(path))),
                      m_gravitationalConstant(
                              static_cast<float>( m_iniReader->getReal("physics", "gravitational_constant", 500.0f))),
                      m_surfaceFriction(static_cast<float>( m_iniReader->getReal("physics", "surface_friction", 0.0f))),
                      m_jumpVelocity(static_cast<float>( m_iniReader->getReal("physics", "jump_velocity", 0.2f))),
                      m_wallJumpYVelocity(
                              static_cast<float>( m_iniReader->getReal("physics", "wall_jump_y_velocity", 200.0f))),
                      m_wallJumpXVelocity(
                              static_cast<float>( m_iniReader->getReal("physics", "wall_jump_x_velocity", 200.0f))),
                      m_maxHorizontalSpeed(
                              static_cast<float>( m_iniReader->getReal("physics", "max_horizontal_speed", 200.0f))),
                      m_maxVerticalSpeed(
                              static_cast<float>( m_iniReader->getReal("physics", "max_vertical_speed", 200.0f))) {
                m_iniReader.reset(nullptr);
            }

        private:
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
