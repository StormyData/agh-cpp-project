//
// Created by tobiasz on 21.05.2022.
//

#pragma once
#include <utility>

#include "../game/GameData.h"

class Collidable {
    ColisionData data;
    sf::Vector2f position = {0,0};
protected:
    explicit Collidable(ColisionData data) : data(std::move(data)) {}
    void update_position(sf::Vector2f pos){position = pos;};
public:
    bool colides(const Collidable& other);
};


