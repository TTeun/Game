//
// Created by pc on 4/27/20.
//

#include "model.h"

void Model::Model::update(float dt)
{
    m_entityList.update(dt);
}

const Entities::EntityList & Model::Model::getEntityList() const
{
    return m_entityList;
}
