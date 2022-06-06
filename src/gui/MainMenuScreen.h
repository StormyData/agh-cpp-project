#pragma once
#include <SFML/Graphics.hpp>
#include "../system/context.h"
#include "Screen.h"
#include "Button.h"

class MainMenuScreen : public Screen
{
public:
    explicit MainMenuScreen(Context& context);
    bool process_additional_event(sf::Event &) override;
    bool update_logic(float) override;
    void draw() override;
private:
    void on_enter() override { context.soundEngine.play_music(context.assetLoader.get_misc_config("main_menu_music"));};
    Button credits_button;
    Button play_button;
    bool goto_credits = false;
    bool goto_play = false;
    sf::Sprite background_sprite;
    sf::Text title;
};