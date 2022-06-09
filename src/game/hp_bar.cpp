#include "hp_bar.h"

sf::Color interpolate(float percent) {
    const sf::Vector3f lower(0, 255, 0);
    const sf::Vector3f upper(255, 0, 0);
    sf::Vector3i color = sf::Vector3i(lower * percent + upper * (1.0f - percent));
    return {(unsigned char) color.x, (unsigned char) color.y, (unsigned char) color.z, 255};
}


HPBar::HPBar(int max_hp, sf::Vector2f offset) : max_hp(max_hp), current_hp(max_hp) {
    if (max_hp < 0)
        throw std::invalid_argument("max_hp cannot be negative");

    start_offset = offset - sf::Vector2f(size.x * (float) max_hp / 2.0f, size.y);
}

void HPBar::set_hp(int hp) {
    if (hp < 0 || hp > max_hp)
        throw std::invalid_argument("hp outside allowed range");
    current_hp = hp;
}

void HPBar::draw(sf::RenderTarget &target, sf::RenderStates states) const {

    sf::RectangleShape shape;
    shape.setSize(size);
    shape.setOutlineColor(sf::Color::White);
    shape.setOutlineThickness(-2);
    for (int i = 0; i < max_hp; i++) {
        sf::Vector2f this_pos = start_offset + pos;
        this_pos.x += (float) i * size.x;
        shape.setPosition(this_pos);
        if (i < current_hp) {
            shape.setFillColor(interpolate((float) i / (float) (max_hp - 1)));
        } else {
            shape.setFillColor(sf::Color::Transparent);
        }
        target.draw(shape, states);
    }
}
