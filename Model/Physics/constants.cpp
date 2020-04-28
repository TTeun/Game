//
// Created by pc on 4/27/20.
//

#include "constants.h"

#include "../../ThirdParty/inih-master/cpp/INIReader.h"

std::unique_ptr<Model::Physics::Constants> Model::Physics::Constants::readIniFile()
{
    INIReader iniReader("../Config/physics.ini");

    if (iniReader.ParseError() == -1) {
        return std::make_unique<Model::Physics::Constants>(Constants{});
    }

    double gravitationalConstant = iniReader.GetReal("physics", "gravitational_constant", 0.0f);
    double surfaceFriction       = iniReader.GetReal("physics", "surface_friction", 0.0f);
    double jumpVelocity          = iniReader.GetReal("physics", "jump_velocity", 0.2f);
    double wallJumpYVelocity     = iniReader.GetReal("physics", "wall_jump_y_velocity", 200.0f);
    double wallJumpXVelocity     = iniReader.GetReal("physics", "wall_jump_x_velocity", 200.0f);
    double maxHorizontalSpeed    = iniReader.GetReal("physics", "max_horizontal_speed", 200.0f);

    return std::make_unique<Model::Physics::Constants>(Constants{static_cast<float>(gravitationalConstant),
                                                                 static_cast<float>(surfaceFriction),
                                                                 static_cast<float>(jumpVelocity),
                                                                 static_cast<float>(wallJumpYVelocity),
                                                                 static_cast<float>(wallJumpXVelocity),
                                                                 static_cast<float>(maxHorizontalSpeed)});
}
