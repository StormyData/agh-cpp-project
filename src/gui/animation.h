#include <SFML/Graphics.hpp>

#pragma once

struct AnimationData {
    const sf::Texture *texture;
    sf::Vector2i frame_size;
    int frames_in_row;
    std::vector<float> times;
};

class Animation : public sf::Drawable {
public:
    explicit Animation(const AnimationData &data, float initial_time = 0);

    bool update(float dt);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override { target.draw(sprite, states); }

    void setPosition(sf::Vector2f pos) { sprite.setPosition(pos); }

    sf::Vector2f getSize();

private:
    const AnimationData animation_data;
    sf::Sprite sprite;
    float time = 0;
    size_t index = 0;
};


