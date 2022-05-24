//
// Created by tobiasz on 09.05.2022.
//

#include "MainMenuScreen.h"
#include <SFML/Graphics.hpp>
#include "../system/AssetLoader.h"
MainMenuScreen::MainMenuScreen(Context &context) : Screen(context),
    enemy1(context.assetLoader.get_animation("enemy_1")),
    background_sprite(context.assetLoader.get_texture("main_menu_background"))
{
    ButtonProperties start_button_properties;
    start_button_properties.text = "start game";
    start_button_properties.where = sf::FloatRect(0, 0, 800, 600);
    start_button_properties.v_align = start_button_properties.h_align = Alignment::CENTER;
    bool& go_to_game = goto_game;
    start_button_properties.onClick = [&go_to_game](){ go_to_game = true;};
    start_button = Button(start_button_properties, context.assetLoader);
}

bool MainMenuScreen::process_additional_event(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        start_button.test_click(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y));
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        return start_button.test_mouseover(sf::Vector2f(sf::Mouse::getPosition(context.window)));
    }
    return false;
}

bool MainMenuScreen::update_logic(float dt) {
    if(goto_game)
    {
        std::cout << "gone to game, and returned from game\n";
        goto_game = false;
    }
    return enemy1.update(dt);
}

void MainMenuScreen::draw() {
    context.window.draw(background_sprite);
    context.window.draw(start_button);
    context.window.draw(enemy1);
}
