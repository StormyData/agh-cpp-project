#pragma once

#include <SFML/Graphics.hpp>
#include <vector>
#include <list>
#include <optional>
#include "../gui/screen.h"
#include "visual_effect.h"
#include "game_data.h"

class Projectile;

class Ship;

struct Context;


class Level : public Screen {
public:
    Level(const LevelData &data, Context &context);

    void draw() override;

    bool process_additional_event(sf::Event &) override;

    bool update_logic(float) override;

    static Screen *get_level_screen(Context &context, unsigned int n);

    void add_projectile(Projectile *);

    void add_effect(const std::string &name, sf::Vector2f pos) { effect_holder.create_effect(pos, name); };

    ~Level();

private:
    void on_enter() override;

    EffectHolder effect_holder;
    const LevelData data;
    sf::Sprite background;
    std::list<Ship *> ships;
    std::list<Projectile *> projectiles;
    size_t n_of_enemies;
    Ship *player;

    void on_defeat();
};
