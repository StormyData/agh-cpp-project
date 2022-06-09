#pragma once


#include <SFML/System/Vector2.hpp>

struct Context;

class BaseAI {
protected:
    constexpr const static float base_speed = 60.0f;
public:
    virtual sf::Vector2f update(float dt, sf::Vector2i wall_collisions) = 0;

    virtual ~BaseAI() = default;
};


class LeftToRightAI : public BaseAI {
    enum Side : int {
        LEFT = -1, RIGHT = 1, DOWN = 0
    } side = RIGHT;
    Side last_moved_side = RIGHT;

    float dist = 0;
    Context &context;
public:
    explicit LeftToRightAI(Context &context, bool flipped) : context(context) {
        if (flipped) {
            side = LEFT;
            last_moved_side = LEFT;
        }
    }

    sf::Vector2f update(float dt, sf::Vector2i wall_collisions) override;
};

class StaticAI : public BaseAI {
public:
    sf::Vector2f update(float dt, sf::Vector2i wall_collisions) override { return {0, 0}; }
};

class LeftToRightSinesAI : public BaseAI {
    int side = 1;
    float variable = 0;
public:
    sf::Vector2f update(float dt, sf::Vector2i wall_collisions) override;
};

class LeftToRightSineSpeedUpDownCosAI : public BaseAI {
    int side = 1;
    float variable = 0;
public:
    sf::Vector2f update(float dt, sf::Vector2i wall_collisions) override;
};

class MovingInCircleAI : public BaseAI {
    float variable = 0;
public:
    sf::Vector2f update(float dt, sf::Vector2i wall_collisions) override;
};

class MovingInEightsAI : public BaseAI {
    float variable = 0;
public:
    sf::Vector2f update(float dt, sf::Vector2i wall_collisions) override;
};

class DiagonallyMovingAI : public BaseAI {
    float variable = 0;
public:
    sf::Vector2f update(float dt, sf::Vector2i wall_collisions) override;
};

class PolynomialMovingAI : public BaseAI {
    int side = 1;
    float variable = 0;
    float variable_2 = -2;
public:
    sf::Vector2f update(float dt, sf::Vector2i wall_collisions) override;
};