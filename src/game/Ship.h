//
// Created by tobiasz on 17.05.2022.
//

#pragma once

#include "GameData.h"
#include "../system/AssetLoader.h"
#include "../system/Collidable.h"
#include "Projectile.h"
class Ship : public sf::Drawable, private Collidable
{
protected:
    int timer;
    int health;
    Side side;
    bool is_dead = false;
    Animation animation;
public:
    Ship(const ShipData& shipData, const AssetLoader& assetLoader);
    bool get_hit_by(const Projectile& projectile);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    virtual void update(float dt);
};

class PlayerShip : public Ship
{
    PlayerShip(const ShipData& shipData, const AssetLoader& assetLoader);
};

class Boss : public Ship
{

};