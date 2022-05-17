#pragma once


#include <SFML/Graphics/Rect.hpp>

enum Alignment{
    LOWER,
    CENTER,
    HIGHER
};


namespace util{
    sf::Vector2f align(sf::FloatRect box, sf::Vector2f size, Alignment h_align, Alignment v_align);
}