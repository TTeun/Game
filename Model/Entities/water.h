//
// Created by pc on 4/30/20.
//

#ifndef TEUN_GAME_WATER_H
#define TEUN_GAME_WATER_H

#include "../../View/drawable.h"
#include "../Geometry/quadrilateral.h"
#include "level.h"

namespace Model {
    namespace Physics {
        class Constants;
    }
} // namespace Model

namespace Model {
    namespace Entities {

        class Water : public View::Drawable {

        public:
            Water(Model::Geometry::Rectangle && rectangle);

            void draw(View::Window & window) const override;

            void update(float dt, const Model::Entities::Level & level, const Model::Physics::Constants & constants);

            const Model::Geometry::Rectangle & getRectangle() const;

            const sf::VertexArray & getVertexArray() const;

        private:
            void buildVertexArray();

            sf::VertexArray m_vertexArray;

            float evalWaterHeightAt(float x) const;

            class Wave {
            public:
                Wave(float amplitude, float angularFrequency, float waveLength);

                const float m_amplitude;
                const float m_waveLength;
                const float m_angularFrequency;
            };

            std::vector<Wave> m_waves;

            const Model::Geometry::Rectangle m_shape;

            float m_time = 0.0f;

            const size_t m_quadrilateralCount = 100;
        };

    } // namespace Entities
} // namespace Model

#endif // TEUN_GAME_WATER_H
