#pragma once

#include "game_data.h"
#include "../system/collidable.h"
#include "hp_bar.h"
#include <memory>

class BaseAI;

class Projectile;

class Level;

struct Context;

class Ship : public sf::Drawable, private Collidable {
protected:
    int health;
    Side side;
    sf::Vector2i wall_collision{0, 0};
    sf::Vector2f speed{0, 0};
    sf::Vector2f position;
    bool is_dead = false;
    Animation animation;
    Context &context;
    Level *level_ptr;
    HPBar hpBar;
    std::vector<std::pair<ProjectileData, sf::Vector2f>> fired_projectiles;
public:
    Ship(const ShipData *shipData, Side side, Context &context, Level *);

    bool get_hit_by(const Projectile &projectile);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    virtual void update(float dt);

    bool is_destroyed() const { return is_dead; }

    void fire_projectiles();
};

class EnemyShip : public Ship {
    float timer;
    std::unique_ptr<BaseAI> ai;
public:
    EnemyShip(const EnemyShipData *shipData, Context &context, Level *);

    void update(float dt) override;

};

class PlayerShip : public Ship {
public:
    PlayerShip(Level *level, const PlayerData *shipData, Context &context);

    void update(float dt) override;

private:
    float reset_timer;
    float timer = 0;
    float speed_change = 180;

    void handle_keyboard();
};
