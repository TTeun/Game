//
// Created by pc on 4/26/20.
//

#ifndef SFML_CONSTANTS_H
#define SFML_CONSTANTS_H

namespace Physics {
    struct Constants {

        static Constants * readIniFile();

        const float m_gravitationalConstant = 500.0f;
        const float m_surfaceFriction       = 10.0f;
        const float m_jumpVelocity          = 600.0f;
        const float m_wallJumpYVelocity     = 600.0f;
        const float m_wallJumpXVelocity     = 200.0f;
        const float m_maxHorizontalSpeed    = 500.0f;
    };
} // namespace Physics

#endif // SFML_CONSTANTS_H