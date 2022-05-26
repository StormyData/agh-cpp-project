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

}

Level::Level(const LevelData &data, Context &context) : Screen(context,false), data(data)
{
    n_of_enemies = data.ships.size();
    background.setTexture(context.assetLoader.get_texture(data.background),true);
    for(const auto& ship_blueprint : data.ships)
        ships.push_back(new Ship(ship_blueprint, context.assetLoader));
}

bool Level::process_additional_event(sf::Event &event) {
    return false;
}

bool Level::update_logic(float dt) {
    bool should_update = false;
    if(n_of_enemies == 0)
    {
        set_return(get_level_screen(context,data.next_level_no));
    }
//    {
//        Screen* main = new MainMenuScreen(context);
//        displayText displayText;
//        displayText.text = "Defeat!!!";
//        displayText.style = 0;
//        displayText.size = 70;
//        return new TimedTextScreen(context, displayText, 1, "main_menu_background", main);
//    }

    return should_update;
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
