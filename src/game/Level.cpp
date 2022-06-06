#include <optional>
#include "Level.h"
#include "Ship.h"
#include "../gui/auxilary_screens.h"
#include "../gui/MainMenuScreen.h"

void Level::draw() {
    context.window.draw(background);
    for(Projectile* p : projectiles)
    {
        context.window.draw(*p);
    }
    for(Ship* p : ships)
    {
        context.window.draw(*p);
    }
    context.window.draw(effectHolder);

}

Level::Level(const LevelData &data, Context &context) : Screen(context,false),
effectHolder(context), data(data)
{
    n_of_enemies = data.ships.size();
    background.setTexture(context.assetLoader.get_texture(data.background),true);
    for(const auto& ship_blueprint : data.ships)
        ships.push_back(new EnemyShip(&ship_blueprint, context, this));

    player = new PlayerShip(this, &context.assetLoader.get_player_ship_data(), context);
    ships.push_back(player);
}

bool Level::process_additional_event(sf::Event &event) {
    return false;
}

bool Level::update_logic(float dt) {
    effectHolder.update(dt);

    if(n_of_enemies == 0)
    {
        context.soundEngine.play_sound("jump_sound");
        set_return(get_level_screen(context,data.next_level_no));
    }
    for(Ship* ship : ships)
    {
        ship->update(dt);
    }
    sf::Vector2f screen_size = (sf::Vector2f)context.window.getSize();
    for(auto projectile_it = projectiles.begin(); projectile_it != projectiles.end();)
    {
        (*projectile_it)->update(dt);
        sf::Vector2f projectile_pos = (*projectile_it)->getPosition();
        if(projectile_pos.x < 0 || projectile_pos.x > screen_size.x ||
            projectile_pos.y < 0 || projectile_pos.y > screen_size.y)
        {
            delete *projectile_it;
            projectile_it = projectiles.erase(projectile_it);
        }
        else
            projectile_it++;
    }
    for(auto ship_it = ships.begin(); ship_it != ships.end();)
    {
        bool removed = false;
        for(auto projectile_it = projectiles.begin(); projectile_it != projectiles.end();)
        {
            if((*ship_it)->get_hit_by(**projectile_it))
            {
                delete *projectile_it;
                projectile_it = projectiles.erase(projectile_it);
                if((*ship_it)->is_destroyed())
                {
                    if(*ship_it == player)
                    {
                        on_defeat();
                        return true;
                    }
                    else
                    {
                        n_of_enemies--;
                    }
                    delete *ship_it;
                    removed = true;
                    break;
                }
            } else
                projectile_it++;
        }
        if(removed)
            ship_it = ships.erase(ship_it);
        else
            ship_it++;
    }
    return true;
}

void Level::on_defeat() {
    Screen* main = new MainMenuScreen(context);
    displayText displayText;
    displayText.text = "Defeat!!!";
    displayText.style = 0;
    displayText.size = 70;
    set_return(new TimedTextScreen(context, displayText, 1, "main_menu_background", main));
}


Screen *Level::get_level_screen(Context& context, unsigned int n) {
    if(n >= context.assetLoader.get_levels().size())
    {
        Screen* main = new MainMenuScreen(context);
        displayText dt;
        dt.text = "Victory!!!";
        dt.style = 0;
        dt.size = 70;
        return new TimedTextScreen(context,dt, 3, "main_menu_background", main);
    }
    LevelData data = context.assetLoader.get_levels()[n];
    Screen* main = new Level(data,context);
    displayText dt;
    dt.text = data.display_name;
    dt.style = 0;
    dt.size = 70;
    return new TimedTextScreen(context,dt, 1, data.background, main);
}

void Level::add_projectile(Projectile * projectile) {
    projectiles.push_back(projectile);
    context.soundEngine.play_sound(projectile->data.firing_sound_name);
}

Level::~Level() {
    std::destroy(ships.begin(), ships.end());
    std::destroy(projectiles.begin(), projectiles.end());
}
