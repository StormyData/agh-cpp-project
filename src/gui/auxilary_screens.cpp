//
// Created by tobiasz on 24.05.2022.
//

#include "auxilary_screens.h"

bool TimedTextScreen::update_logic(float dt) {
    time_left -= dt;
    if(time_left < 0)
        set_return(next_screen);
    return false;
}

void TimedTextScreen::draw() {
    context.window.draw(background);
    context.window.draw(text_sprite);
}

TimedTextScreen::TimedTextScreen(Context &context, const displayText& displayText, float time,
                                 const std::string &background_name, Screen *next_screen) :
        Screen(context, false), time_left(time), next_screen(next_screen),
        text_sprite(displayText.text, context.assetLoader.get_font()),
        background(context.assetLoader.get_texture(background_name)) {
    sf::FloatRect rect({0.0f,0.0f},sf::Vector2f(context.window.getSize()));

    text_sprite.setCharacterSize(displayText.size);
    text_sprite.setStyle(displayText.style);

    sf::Vector2<float> text_size(text_sprite.getGlobalBounds().width, text_sprite.getGlobalBounds().height);
    sf::Vector2f text_pos = util::align(rect,text_size, CENTER, CENTER);
    text_sprite.setPosition(text_pos);
}

ButtonExitTextScreen::ButtonExitTextScreen(Context &context, const displayText& displayText, const std::string &button,
                                           const std::string& background_name, Screen *next_screen) :
        Screen(context, false), text_sprite(displayText.text, context.assetLoader.get_font()), background(context.assetLoader.get_texture(background_name)),
        next_screen(next_screen) {
    ButtonProperties buttonProperties;
    buttonProperties.text = button;
    sf::FloatRect rect({0.0f,0.0f},sf::Vector2f(context.window.getSize()));
    rect.height/=2;

    text_sprite.setCharacterSize(displayText.size);
    text_sprite.setStyle(displayText.style);

    sf::Vector2<float> text_size(text_sprite.getGlobalBounds().width, text_sprite.getGlobalBounds().height);
    sf::Vector2f text_pos = util::align(rect,text_size, CENTER, CENTER);
    text_sprite.setPosition(text_pos);
    rect.top+=rect.height;
    buttonProperties.where = rect;
    buttonProperties.v_align = CENTER;
    buttonProperties.h_align = CENTER;
    buttonProperties.onClick = [this](){this->set_return(this->next_screen);};
    button_sprite = Button(buttonProperties, context.assetLoader);

}

void ButtonExitTextScreen::draw() {
    context.window.draw(background);
    context.window.draw(text_sprite);
    context.window.draw(button_sprite);
}


bool ButtonExitTextScreen::process_additional_event(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left)
    {
        button_sprite.test_click(sf::Vector2f((float)event.mouseButton.x, (float)event.mouseButton.y));
    }
    else if (event.type == sf::Event::MouseMoved)
    {
        return button_sprite.test_mouseover(sf::Vector2f(sf::Mouse::getPosition(context.window)));
    }
    return false;
}
