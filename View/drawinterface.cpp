//
// Created by pc on 4/26/20.
//

#include "drawinterface.h"

#include "../Model/Entities/entitycontroller.h"
#include "window.h"
#include "../Aux/mathtools.h"

#include <iostream>

void View::DrawInterface::drawModel(View::Window &window, const Model::Entities::EntityController &entityController) {
    const auto &rect = window.getViewRect();
    entityController.draw(window);
}

void View::DrawInterface::draw(const Model::Entities::Enemy &enemy, View::Window &window) {
    window.drawRectangle(enemy.getShape());
}

void View::DrawInterface::draw(const Model::Entities::Player &player, View::Window &window) {
    window.drawRectangle(player.getShape());
}

void View::DrawInterface::draw(const Model::Entities::Debris &debris, View::Window &window) {
    window.drawRectangle(debris.getShape());
}

void View::DrawInterface::draw(const Model::Entities::DebrisExplosion &debrisExplosion, View::Window &window) {
    for (const auto &debris : debrisExplosion.getDebrisVector()) {
        debris.draw(window);
    }
}

void View::DrawInterface::draw(const Water &water, View::Window &window) {
    window.draw(water.getVertexArray());
}


void View::DrawInterface::draw(const Model::Entities::Level &level, View::Window &window) {
    const auto &terrainBlocks = level.getTerrainBlocks();
    for (auto it = terrainBlocks.begin(); it != terrainBlocks.end(); ++it) {
        const auto &shape = (**it).getShape();
//        if (not shape.intersects(viewRect)) {
//            continue;
//        }
        window.drawRectangle((**it).getShape());
    }
}

void View::DrawInterface::draw(const Model::Entities::EntityController &entityController, View::Window &window) {
    entityController.getLevelWrapper().getLevel().draw(window);

    entityController.getPlayer().draw(window);
    entityController.getWater().draw(window);

    for (const auto &enemy : entityController.getEnemies()) {
        enemy.draw(window);
    }

    for (const auto &debrisExplosion : entityController.getDebrisExplosions()) {
        debrisExplosion.draw(window);
    }
}

void View::DrawInterface::draw(const Model::DataStructures::RectGraph &rectGraph, View::Window &window) {
    const auto &rectangles = rectGraph.getRectangles();
    const auto &edges = rectGraph.getEdges();
    const auto &edgesToTarget = rectGraph.getEdgesToTarget();


    for (const auto &rectangle : rectangles) {
        window.drawRectangle(rectangle);
    }
    if (rectGraph.hasTarget()) {
        for (auto i : edgesToTarget) {
            window.drawLine(rectangles.at(i.first).getCenter(),
                            rectGraph.getTarget()->getCenter(),
                            {255,
                             static_cast<sf::Uint8>(Aux::clamp(0.3f * i.second, 0, 255)),
                             static_cast<sf::Uint8>(255 - Aux::clamp(0.3f * i.second, 0, 255))});
        }
    }

    for (const auto &edge : edges) {
        window.drawLine(rectangles.at(edge.first.first).getCenter(),
                        rectangles.at(edge.first.second).getCenter(),
                        {100, 100, 100});
    }


}