//
// Created by tobiasz on 09.05.2022.
//

#include "MainMenuScreen.h"
#include <SFML/Graphics.hpp>
#include "../gui/auxilary_screens.h"
MainMenuScreen::MainMenuScreen(Context &context) : Screen(context, false),
    enemy1(context.assetLoader.get_animation("enemy_1")),
    background_sprite(context.assetLoader.get_texture("main_menu_background"))
{
    ButtonProperties start_button_properties;
    start_button_properties.text = "credits";
    start_button_properties.where = sf::FloatRect(0, 0, 800, 600);
    start_button_properties.v_align = start_button_properties.h_align = Alignment::CENTER;
    start_button_properties.onClick = [this](){ this->goto_credits = true;};
    credits_button = Button(start_button_properties, context.assetLoader);
}

bool MainMenuScreen::process_additional_event(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        credits_button.test_click(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y));
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        return credits_button.test_mouseover(sf::Vector2f(sf::Mouse::getPosition(context.window)));
    }
    return false;
}

bool MainMenuScreen::update_logic(float dt) {
    if(goto_credits)
    {
        Screen* back = new MainMenuScreen(context);
        Screen* s = new ButtonExitTextScreen(context,context.assetLoader.get_string("credits"),"back","main_menu_background", back);
        set_return(s);
        goto_credits = false;
    }
    return enemy1.update(dt);
}

void MainMenuScreen::draw() {
    context.window.draw(background_sprite);
    context.window.draw(credits_button);
    context.window.draw(enemy1);
}
