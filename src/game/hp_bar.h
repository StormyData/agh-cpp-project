#pragma once

#include <SFML/Graphics.hpp>

class HPBar : public sf::Drawable {
public:
    HPBar(int max_hp, sf::Vector2f offset);

    void set_hp(int hp);

    void set_position(sf::Vector2f new_pos) { pos = new_pos; }

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

private:
    int max_hp;
    int current_hp;
    sf::Vector2f start_offset;
    const sf::Vector2f size{10, 10};
    sf::Vector2f pos;
};


