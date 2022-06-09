#pragma once

#include <utility>

#include "../game/game_data.h"

class Collidable {
    CollisionData data;
    sf::Vector2f position = {0, 0};
    std::vector<std::pair<float, float>> min_max_arr;
    std::vector<sf::Vector2f> axes;

    [[nodiscard]] bool sat(const Collidable &other) const;

protected:
    explicit Collidable(const CollisionData &data);

    void update_position(sf::Vector2f pos) { position = pos; };
public:
    bool collides(const Collidable &other);
};


