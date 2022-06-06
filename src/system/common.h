#pragma once


#include <SFML/Graphics/Rect.hpp>
#include <cmath>

enum Alignment{
    LOWER,
    CENTER,
    HIGHER
};


namespace util{
    sf::Vector2f align(sf::FloatRect box, sf::Vector2f size, Alignment h_align, Alignment v_align);

    template<typename T>
    sf::Vector2<T> rotate_90_degrees_clockwise(sf::Vector2<T> vec){return {vec.y, -vec.x};}
    template<typename T>
    T dot(sf::Vector2<T> left, sf::Vector2<T> right)
    {
        return left.x * right.x + left.y * right.y;
    }
    template<typename T>
    sf::Vector2<T> normalize(sf::Vector2<T> vec)
    {
        T len = hypot(vec.x, vec.y);
        if(len > 0)
            return vec / len;
        else
            return {0, 0};
    }
}