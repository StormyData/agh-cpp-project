//
// Created by tobiasz on 06.06.2022.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../gui/Animation.h"
#include "../system/context.h"
#include <list>

class Effect: public sf::Drawable{
public:
    Effect(sf::Vector2f pos, const AnimationData& data);
    bool update(float dt);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
private:
    AnimationData animationData;
    sf::Sprite sprite;
    size_t index = 0;
    float time = 0;
};

class EffectHolder: public sf::Drawable{
public:
    explicit EffectHolder(Context& context): context(context) {}
    void create_effect(sf::Vector2f pos, const std::string& name);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    void update(float dt);
private:
    std::list<Effect> effects;
    Context& context;
};
