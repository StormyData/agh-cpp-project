#include <cmath>
#include "enemy_ais.h"
#include "../system/context.h"


sf::Vector2f LeftToRightAI::update(float dt, sf::Vector2i wall_collisions) {
    if ((wall_collisions.x == 1 && side == 1) || (wall_collisions.x == -1 && side == -1)) {
        last_moved_side = side;
        side = DOWN;
    }
    if (dist * 10 > (float) context.window.getSize().y) // 1/10 of the screen height
    {
        dist = 0;
        side = static_cast<Side>(-last_moved_side);
    }
    switch (side) {
        case DOWN:
            dist += base_speed * dt;
            return {0, base_speed};
        case RIGHT:
            return {base_speed, 0};
        case LEFT:
            return {-base_speed, 0};
        default:
            return {0, 0};
    }
}

sf::Vector2f LeftToRightSinesAI::update(float dt, sf::Vector2i wall_collisions) {
    if (wall_collisions.x == 1 && side == 1)
        side = -1;
    if (wall_collisions.x == -1 && side == -1)
        side = 1;
    variable += 0.01f * dt * base_speed;
    return {base_speed * (float) side, std::sin(variable) * base_speed};

}

sf::Vector2f LeftToRightSineSpeedUpDownCosAI::update(float dt, sf::Vector2i wall_collisions) {
    if (wall_collisions.x == 1 && side == 1)
        side = -1;
    if (wall_collisions.x == -1 && side == -1)
        side = 1;
    variable += 0.01f * dt * base_speed;
    return {fabsf(std::sin(variable)) * (float) side * 1.5f * base_speed, std::cos(variable) * base_speed};
}

sf::Vector2f MovingInCircleAI::update(float dt, sf::Vector2i wall_collisions) {
    variable += 0.01f * dt * base_speed;
    return {std::cos(variable) * base_speed, std::sin(variable) * base_speed};

}

sf::Vector2f MovingInEightsAI::update(float dt, sf::Vector2i wall_collisions) {
    variable += 0.01f * dt * base_speed;
    return {std::cos(variable) * base_speed, std::cos(variable * 2) * base_speed};
}

sf::Vector2f DiagonallyMovingAI::update(float dt, sf::Vector2i wall_collisions) {
    variable += 0.02f * dt * base_speed;
    return {std::cos(variable) * base_speed, std::cos(variable) * base_speed};
}

sf::Vector2f PolynomialMovingAI::update(float dt, sf::Vector2i wall_collisions) {
    if (wall_collisions.x == 1 && side == 1)
        side = -1;
    if (wall_collisions.x == -1 && side == -1)
        side = 1;
    variable += 0.01f * dt * base_speed;
    variable_2 += 0.01f * dt * base_speed;
    if (variable > 1.9)
        variable = -2.3f;
    return {static_cast<float>((variable + 2) * (variable + 1) * (variable - 0.5) * (variable - 1.5) * side *
                               base_speed),
            std::cos(variable_2) * base_speed};

}
