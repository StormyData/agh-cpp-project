//
// Created by tobiasz on 17.05.2022.
//

#include <iostream>
#include "Animation.h"


bool Animation::update(float dt) {
    time+=dt;
    size_t last_index = index;
    while(animationData.times[index] <= time)
    {
        time-= animationData.times[index];
        index++;
        if(index >= animationData.times.size())
            index = 0;
    }
    if(index != last_index)
    {
        int y = index / animationData.frames_in_row;
        int x = index % animationData.frames_in_row;
        sf::Vector2i pos(x * animationData.frame_size.x, y * animationData.frame_size.y);
        sprite.setTextureRect(sf::IntRect(pos, animationData.frame_size));
        return true;
    }
    return false;
}

Animation::Animation(const AnimationData &data, float initial_time)
        : animationData(data), sprite(*(data.texture)){
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0), data.frame_size));
    update(initial_time);
}

