#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include "../system/AssetLoader.h"
#include "GameData.h"
#include "Projectile.h"
#include "../system/context.h"
#include "../gui/Screen.h"
#include "visual_effect.h"
#include <optional>
class Ship;

class Level: public Screen{
public:
    Level(const LevelData& data,Context& context);
    void draw() override;
    bool process_additional_event(sf::Event &) override;
    bool update_logic(float) override;

    static Screen *get_level_screen(Context& context, unsigned int n);
    void add_projectile(Projectile*);
    void add_effect(const std::string& name, sf::Vector2f pos){effectHolder.create_effect(pos, name);};
    ~Level();
private:
    EffectHolder effectHolder;
    const LevelData data;
    sf::Sprite background;
    std::list<Ship*> ships;
    std::list<Projectile*> projectiles;
    size_t n_of_enemies;
    Ship* player;
    void on_defeat();
};

//class Boss_level : public Level
//{
//
//};
