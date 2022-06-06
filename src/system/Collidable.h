//
// Created by tobiasz on 21.05.2022.
//

#pragma once
#include <utility>

#include "../game/GameData.h"

class Collidable {
    ColisionData data;
    sf::Vector2f position = {0,0};
    std::vector<std::pair<float, float>> min_max_arr;
    std::vector<sf::Vector2f> axes;
    bool sat(const Collidable& other) const;
protected:
    explicit Collidable(const ColisionData& data);
    void update_position(sf::Vector2f pos){position = pos;};
public:
    bool colides(const Collidable& other);
};


