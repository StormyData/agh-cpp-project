#include <optional>
#include "level.h"
#include "ships.h"

#include "../gui/auxiliary_screens.h"
#include "../gui/main_menu_screen.h"
#include "../system/context.h"
#include "projectile.h"

void Level::draw() {
    context.window.draw(background);
    for (Projectile *p: projectiles) {
        context.window.draw(*p);
    }
    for (Ship *p: ships) {
        context.window.draw(*p);
    }
    context.window.draw(effect_holder);

}

Level::Level(const LevelData &data, Context &context) : Screen(context, false),
                                                        effect_holder(context), data(data) {
    n_of_enemies = data.ships.size();
    background.setTexture(context.asset_loader.get_texture(data.background), true);
    for (const auto &ship_blueprint: data.ships)
        ships.push_back(new EnemyShip(&ship_blueprint, context, this));

    player = new PlayerShip(this, &context.asset_loader.get_player_ship_data(), context);
    ships.push_back(player);
}

bool Level::process_additional_event(sf::Event &event) {
    return false;
}

bool Level::update_logic(float dt) {
    effect_holder.update(dt);

    if (n_of_enemies == 0) {
        context.sound_engine.play_sound(context.asset_loader.get_misc_config("level_switch_sound"));
        set_return(get_level_screen(context, data.next_level_no));
    }
    for (Ship *ship: ships) {
        ship->update(dt);
    }
    sf::Vector2f screen_size = (sf::Vector2f) context.window.getSize();
    for (auto projectile_it = projectiles.begin(); projectile_it != projectiles.end();) {
        (*projectile_it)->update(dt);
        sf::Vector2f projectile_pos = (*projectile_it)->getPosition();
        if (projectile_pos.x < 0 || projectile_pos.x > screen_size.x ||
            projectile_pos.y < 0 || projectile_pos.y > screen_size.y) {
            delete *projectile_it;
            projectile_it = projectiles.erase(projectile_it);
        } else
            projectile_it++;
    }
    for (auto ship_it = ships.begin(); ship_it != ships.end();) {
        bool removed = false;
        for (auto projectile_it = projectiles.begin(); projectile_it != projectiles.end();) {
            if ((*ship_it)->get_hit_by(**projectile_it)) {
                delete *projectile_it;
                projectile_it = projectiles.erase(projectile_it);
                if ((*ship_it)->is_destroyed()) {
                    if (*ship_it == player) {
                        on_defeat();
                        return true;
                    } else {
                        n_of_enemies--;
                    }
                    delete *ship_it;
                    removed = true;
                    break;
                }
            } else
                projectile_it++;
        }
        if (removed)
            ship_it = ships.erase(ship_it);
        else
            ship_it++;
    }
    return true;
}

void Level::on_defeat() {
    Screen *main = new MainMenuScreen(context);
    displayText display_text;
    display_text.text = "Defeat!!!";
    display_text.style = 0;
    display_text.size = 70;
    set_return(
            new TimedTextScreen(context, display_text, 1, context.asset_loader.get_misc_config("main_menu_background"),
                                main));
}


Screen *Level::get_level_screen(Context &context, unsigned int n) {
    if (n >= context.asset_loader.get_levels().size()) {
        Screen *main = new MainMenuScreen(context);
        displayText dt;
        dt.text = "Victory!!!";
        dt.style = 0;
        dt.size = 70;
        return new TimedTextScreen(context, dt, 3, context.asset_loader.get_misc_config("main_menu_background"), main);
    }
    LevelData data = context.asset_loader.get_levels()[n];
    Screen *main = new Level(data, context);
    displayText display_text;
    display_text.text = data.display_name;
    display_text.style = 0;
    display_text.size = 70;
    return new TimedTextScreen(context, display_text, 1, data.background, main);
}

void Level::add_projectile(Projectile *projectile) {
    projectiles.push_back(projectile);
    context.sound_engine.play_sound(projectile->data.firing_sound_name);
}

Level::~Level() {
    std::destroy(ships.begin(), ships.end());
    std::destroy(projectiles.begin(), projectiles.end());
}

void Level::on_enter() {
    context.sound_engine.play_music(context.asset_loader.get_misc_config("game_music"));
}
