//
// Created by tobiasz on 24.05.2022.
//

#pragma once
#include "Screen.h"
#include "Button.h"


class TimedTextScreen : public Screen
{
public:
    explicit TimedTextScreen(Context& context, const displayText& displayText, float time, const std::string& background_name, Screen* next_screen);

protected:
    float time_left;
    Screen* next_screen;
    sf::Text text_sprite;
    sf::Sprite background;
    bool update_logic(float) override;
    void draw() override;
    bool process_additional_event(sf::Event &) override {return false;};

};

class ButtonExitTextScreen : public Screen
{
public:
    explicit ButtonExitTextScreen(Context& context, const displayText& displayText, const std::string& button_text, const std::string& background_name,Screen* next_screen);

protected:
    sf::Text text_sprite;
    Button button_sprite;
    sf::Sprite background;
    bool update_logic(float) override {return false;};
    void draw() override;
    bool process_additional_event(sf::Event &) override;
    Screen* next_screen;
};