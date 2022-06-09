#include "visual_effect.h"
#include "../system/context.h"

bool Effect::update(float dt) {
    time += dt;
    size_t last_index = index;
    while (animation_data.times[index] <= time) {
        time -= animation_data.times[index];
        index++;
        if (index >= animation_data.times.size())
            return true;
    }

    if (index != last_index) {
        unsigned int y = index / animation_data.frames_in_row;
        unsigned int x = index % animation_data.frames_in_row;
        sf::Vector2i pos(x * animation_data.frame_size.x, // NOLINT(cppcoreguidelines-narrowing-conversions)
                         y * animation_data.frame_size.y); // NOLINT(cppcoreguidelines-narrowing-conversions)
        sprite.setTextureRect(sf::IntRect(pos, animation_data.frame_size));
    }
    return false;
}

Effect::Effect(sf::Vector2f pos, const AnimationData &data) : animation_data(data), sprite(*(data.texture)) {
    sprite.setTextureRect(sf::IntRect(sf::Vector2i(0, 0), data.frame_size));
    sprite.setPosition(pos - sf::Vector2f(data.frame_size) / 2.0f);
}

void Effect::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}


void EffectHolder::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    std::for_each(effects.begin(), effects.end(), [&](const Effect &item) {
        target.draw(item, states);
    });
}

void EffectHolder::update(float dt) {
    effects.remove_if([dt](Effect &effect) { return effect.update(dt); });
}

void EffectHolder::create_effect(sf::Vector2f pos, const std::string &name) {
    effects.emplace_back(pos, context.asset_loader.get_animation(name));
}
