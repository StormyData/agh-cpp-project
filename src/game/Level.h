#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "../system/AssetLoader.h"
#include "GameData.h"
#include "Projectile.h"
#include "../system/context.h"
#include "../gui/Screen.h"
#include <optional>
class Ship;

class Level: public Screen{
public:
    Level(const LevelData& data,Context& context);
    void draw() override;
    bool process_additional_event(sf::Event &) override;
    bool update_logic(float) override;

    static Screen *get_level_screen(Context& context, unsigned int n);
private:
    const LevelData data;
    sf::Sprite background;
    std::list<Ship*> ships;
    std::list<Projectile*> projectiles;
    size_t n_of_enemies;

};

//class Boss_level : public Level
//{
//
//};
