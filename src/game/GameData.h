//
// Created by tobiasz on 17.05.2022.
//

#pragma once

#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>
#include "../gui/Animation.h"
enum Side{PLAYER, ENEMY};


struct ColisionData
{
    std::vector<sf::Vector2f> points;
};
struct ProjectileData
{
    Side side = ENEMY;
    const sf::Texture* texture = nullptr;
    ColisionData colision;
    sf::Vector2f speed;
};

struct ShipType
{
    ColisionData colision;
    AnimationData animation;
};


struct ShipData {
    ShipType type;
    int ai_type;
    int hp;
    std::vector<std::pair<ProjectileData, sf::Vector2f>> fired_projectiles;
    sf::Vector2f  start_pos;
};

struct LevelData {
    std::string background;
    std::vector<ShipData> ships;
};