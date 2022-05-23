#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "../system/AssetLoader.h"
#include "GameData.h"
#include "Projectile.h"
#include "../system/context.h"
class Ship;

class Level{
public:
    Level(const LevelData& data,Context& context) : context(context)
    {

    }
    virtual std::optional<int> run(int initial_player_health);
private:
    const LevelData data;
    sf::Sprite background;
    std::list<Ship*> ships;
    std::list<Projectile*> projectiles;
    Context& context;
};

//class Boss_level : public Level
//{
//
//};
