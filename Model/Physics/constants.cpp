#include "constants.h"

Model::Physics::Constants::Constants(std::string path)
    : m_iniReader(std::make_unique<IniReaderWrapper>(IniReaderWrapper(path))),
      m_gravitationalConstant((m_iniReader->getReal("physics", "gravitational_constant", 0.0f))),
      m_surfaceFriction((m_iniReader->getReal("physics", "surface_friction", 0.0f))),
      m_jumpVelocity((m_iniReader->getReal("physics", "jump_velocity", 0.0f))),
      m_wallJumpYVelocity((m_iniReader->getReal("physics", "wall_jump_y_velocity", 0.0f))),
      m_wallJumpXVelocity((m_iniReader->getReal("physics", "wall_jump_x_velocity", 0.0f))),
      m_maxHorizontalSpeed((m_iniReader->getReal("physics", "max_horizontal_speed", 0.0f))),
      m_maxVerticalSpeed((m_iniReader->getReal("physics", "max_vertical_speed", 0.0f)))
{
    m_iniReader.reset(nullptr);
}

std::unique_ptr<Model::Physics::Constants> Model::Physics::Constants::create(std::string path)
{
    return std::unique_ptr<Constants>(new Constants(std::move(path)));
}
