//
// Created by tobiasz on 21.05.2022.
//

#pragma once
#include <SFML/Graphics.hpp>
#include "../system/Collidable.h"

struct Projectile : public Collidable, public sf::Drawable{
    sf::Sprite sprite;
    sf::Vector2f position;
    ProjectileData data;
public:
    explicit Projectile(const ProjectileData& projectileData, sf::Vector2f position);
    void update(float dt);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;
    Side getSide() const { return data.side;};
    sf::Vector2f getPosition() const {return position;};
};


