//
// Created by tobiasz on 21.05.2022.
//

#include "Projectile.h"

void Projectile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Projectile::update(float dt) {
    position+=data.speed * dt;
    sprite.setPosition(position);
}

Projectile::Projectile(const ProjectileData& projectileData, sf::Vector2f position):
Collidable(projectileData.colision), position(position) , data(projectileData) {
}
