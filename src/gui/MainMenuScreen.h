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
    Button start_button;
    bool goto_game = false;
    Animation enemy1;
    sf::Sprite background_sprite;
};