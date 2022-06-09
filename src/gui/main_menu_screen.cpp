#include "main_menu_screen.h"
#include <SFML/Graphics.hpp>
#include "auxiliary_screens.h"
#include "../game/level.h"
#include "../system/context.h"

MainMenuScreen::MainMenuScreen(Context &context) : Screen(context, false),
                                                   background_sprite(context.asset_loader.get_texture(
                                                           context.asset_loader.get_misc_config(
                                                                   "main_menu_background"))) {
    title = sf::Text("OUT OF SPACE", context.asset_loader.get_font(), 70);
    title.setStyle(sf::Text::Bold);
    float windowHeight = (float) context.window.getSize().y;
    sf::FloatRect window_rect({0, 0}, sf::Vector2f(context.window.getSize()));
    window_rect.height /= 2;
    title.setFillColor(sf::Color(0, 0, 0, 255));
    title.setOutlineColor(sf::Color(255, 255, 255, 255));
    title.setOutlineThickness(4);
    sf::Vector2<float> text_size(title.getGlobalBounds().width, title.getGlobalBounds().height);
    sf::Vector2f text_pos = util::align(window_rect, text_size, CENTER, CENTER);
    title.setPosition(text_pos);
    window_rect.height /= 3;
    window_rect.top += windowHeight / 2;

    ButtonProperties play_button_properties;
    play_button_properties.text = "play";
    play_button_properties.where = window_rect;
    play_button_properties.v_align = play_button_properties.h_align = Alignment::CENTER;
    play_button_properties.onClick = [this]() { this->goto_play = true; };
    play_button = Button(play_button_properties, context.asset_loader);

    window_rect.top += windowHeight / 4;

    ButtonProperties credits_button_properties;
    credits_button_properties.text = "credits";
    credits_button_properties.where = window_rect;
    credits_button_properties.v_align = credits_button_properties.h_align = Alignment::CENTER;
    credits_button_properties.onClick = [this]() { this->goto_credits = true; };
    credits_button = Button(credits_button_properties, context.asset_loader);

}

bool MainMenuScreen::process_additional_event(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        sf::Vector2f where((float) event.mouseButton.x, (float) event.mouseButton.y);
        credits_button.test_click(where);
        play_button.test_click(where);
    } else if (event.type == sf::Event::MouseMoved) {
        return credits_button.test_mouseover(sf::Vector2f(sf::Mouse::getPosition(context.window))) || \
        play_button.test_mouseover(sf::Vector2f(sf::Mouse::getPosition(context.window)));
    }
    return false;
}

bool MainMenuScreen::update_logic(float dt) {
    if (goto_credits) {
        Screen *back = new MainMenuScreen(context);
        Screen *s = new ButtonExitTextScreen(context, context.asset_loader.get_string("credits"), "back",
                                             context.asset_loader.get_misc_config("main_menu_background"), back);
        set_return(s);
        goto_credits = false;
    }
    if (goto_play) {
        Screen *s = Level::get_level_screen(context, 0);
        set_return(s);
        goto_play = false;
    }
    return false;
}

void MainMenuScreen::draw() {
    context.window.draw(background_sprite);
    context.window.draw(play_button);
    context.window.draw(title);
    context.window.draw(credits_button);
}

void MainMenuScreen::on_enter() {
    context.sound_engine.play_music(context.asset_loader.get_misc_config("main_menu_music"));
};
