#include "auxiliary_screens.h"
#include "../system/context.h"

bool TimedTextScreen::update_logic(float dt) {
    time_left -= dt;
    if (time_left < 0)
        set_return(next_screen);
    return false;
}

void TimedTextScreen::draw() {
    context.window.draw(background);
    context.window.draw(text_sprite);
}

TimedTextScreen::TimedTextScreen(Context &context, const displayText &displayText, float time,
                                 const std::string &background_name, Screen *next_screen) :
        Screen(context, false), time_left(time), next_screen(next_screen),
        text_sprite(displayText.text, context.asset_loader.get_font()),
        background(context.asset_loader.get_texture(background_name)) {
    sf::FloatRect rect({0.0f, 0.0f}, sf::Vector2f(context.window.getSize()));

    text_sprite.setCharacterSize(displayText.size);
    text_sprite.setStyle(displayText.style);

    sf::Vector2<float> text_size(text_sprite.getGlobalBounds().width, text_sprite.getGlobalBounds().height);
    sf::Vector2f text_pos = util::align(rect, text_size, CENTER, CENTER);
    text_sprite.setPosition(text_pos);
}

ButtonExitTextScreen::ButtonExitTextScreen(Context &context, const displayText &displayText, const std::string &button,
                                           const std::string &background_name, Screen *next_screen) :
        Screen(context, false), text_sprite(displayText.text, context.asset_loader.get_font()),
        background(context.asset_loader.get_texture(background_name)),
        next_screen(next_screen) {
    ButtonProperties button_properties;
    button_properties.text = button;
    sf::FloatRect rect({0.0f, 0.0f}, sf::Vector2f(context.window.getSize()));
    rect.height /= 2;

    text_sprite.setCharacterSize(displayText.size);
    text_sprite.setStyle(displayText.style);

    sf::Vector2<float> text_size(text_sprite.getGlobalBounds().width, text_sprite.getGlobalBounds().height);
    sf::Vector2f text_pos = util::align(rect, text_size, CENTER, CENTER);
    text_sprite.setPosition(text_pos);
    rect.top += rect.height;
    button_properties.where = rect;
    button_properties.v_align = CENTER;
    button_properties.h_align = CENTER;
    button_properties.onClick = [this]() { this->set_return(this->next_screen); };
    button_sprite = Button(button_properties, context.asset_loader);

}

void ButtonExitTextScreen::draw() {
    context.window.draw(background);
    context.window.draw(text_sprite);
    context.window.draw(button_sprite);
}


bool ButtonExitTextScreen::process_additional_event(sf::Event &event) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        button_sprite.test_click(sf::Vector2f((float) event.mouseButton.x, (float) event.mouseButton.y));
    } else if (event.type == sf::Event::MouseMoved) {
        return button_sprite.test_mouseover(sf::Vector2f(sf::Mouse::getPosition(context.window)));
    }
    return false;
}
