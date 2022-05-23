//
// Created by tobiasz on 17.05.2022.
//

#include <iostream>
#include "Animation.h"


bool Animation::update(float dt) {
    time+=dt;
    int last_index = index;
    while(data.times[index] <= time)
    {
        time-= data.times[index];
        index++;
        if(index >= data.times.size())
            index = 0;
    }
    if(index != last_index)
    {
        int y = index / data.frames_in_row;
        int x = index % data.frames_in_row;
        sf::Vector2i pos(x * data.frame_size.x, y * data.frame_size.y);
        sprite.setTextureRect(sf::IntRect(pos, data.frame_size));
        return true;
    }
    return false;
}

Animation::Animation(const AnimationData &data, float initial_time)
        : sprite(*data.texture), data(data){
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0), data.frame_size));
    update(initial_time);
}

