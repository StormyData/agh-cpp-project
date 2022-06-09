#include <iostream>
#include "animation.h"


bool Animation::update(float dt) {
    time += dt;
    size_t last_index = index;
    while (animation_data.times[index] <= time) {
        time -= animation_data.times[index];
        index++;
        if (index >= animation_data.times.size())
            index = 0;
    }
    if (index != last_index) {
        unsigned int y = index / animation_data.frames_in_row;
        unsigned int x = index % animation_data.frames_in_row;
        sf::Vector2i pos(x * animation_data.frame_size.x, // NOLINT(cppcoreguidelines-narrowing-conversions)
                         y * animation_data.frame_size.y); // NOLINT(cppcoreguidelines-narrowing-conversions)
        sprite.setTextureRect(sf::IntRect(pos, animation_data.frame_size));
        return true;
    }
    return false;
}

Animation::Animation(const AnimationData &data, float initial_time)
        : animation_data(data), sprite(*(data.texture)) {
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), data.frame_size));
    update(initial_time);
}

sf::Vector2f Animation::getSize() {
    return {sprite.getGlobalBounds().width, sprite.getGlobalBounds().height};
}

