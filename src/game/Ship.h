//
// Created by tobiasz on 17.05.2022.
//

#pragma once

#include "GameData.h"
#include "../system/AssetLoader.h"
#include "../system/Collidable.h"
#include "Projectile.h"
#include "../system/context.h"
class Level;

class Ship : public sf::Drawable, private Collidable
{
protected:
    int health;
    Side side;
    sf::Vector2i wall_colision{0, 0};
    sf::Vector2f speed{0, 0};
    sf::Vector2f position;
    bool is_dead = false;
    Animation animation;
    Context& context;
    Level* level_ptr;
    std::vector<std::pair<ProjectileData, sf::Vector2f>> fired_projectiles;
public:
    Ship(const ShipData& shipData, Context& context, Level*);
    bool get_hit_by(const Projectile& projectile);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    virtual void update(float dt);
    bool is_destroyed() const {return is_dead;}
    void fire_projectiles();
};
class EnemyShip : public Ship
{

};

class PlayerShip : public Ship
{
public:
    PlayerShip(Level *level, const PlayerData &shipData, Context &context);
    void update(float dt) override;
private:
    float reset_timer;
    float timer = 0;
    float speed_change;
    void handle_keyboard(float  dt);
};

class Boss : public EnemyShip
{

};