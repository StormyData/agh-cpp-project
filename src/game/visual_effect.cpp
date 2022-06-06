//
// Created by tobiasz on 06.06.2022.
//

#include "visual_effect.h"
bool Effect::update(float dt) {
    time+=dt;
    size_t last_index = index;
    while(animationData.times[index] <= time)
    {
        time-= animationData.times[index];
        index++;
        if(index >= animationData.times.size())
            return true;
    }

    if(index != last_index)
    {
        int y = index / animationData.frames_in_row;
        int x = index % animationData.frames_in_row;
        sf::Vector2i pos(x * animationData.frame_size.x, y * animationData.frame_size.y);
        sprite.setTextureRect(sf::IntRect(pos, animationData.frame_size));
    }
    return false;
}

Effect::Effect(sf::Vector2f pos, const AnimationData &data): animationData(data), sprite(*(data.texture))
        {
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0,0), data.frame_size));
    sprite.setPosition(pos - sf::Vector2f(data.frame_size)/2.0f);
}

void Effect::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}


void EffectHolder::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    std::for_each(effects.begin(), effects.end(), [&](const Effect& item){
        target.draw(item, states);
    });
}

void EffectHolder::update(float dt) {
    effects.remove_if([dt](Effect& effect){return effect.update(dt);});
}

void EffectHolder::create_effect(sf::Vector2f pos, const std::string& name) {
    effects.emplace_back(pos, context.assetLoader.get_animation(name));
}
