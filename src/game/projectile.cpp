#include "projectile.h"

void Projectile::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(sprite, states);
}

void Projectile::update(float dt) {
    position += data.speed * dt;
    sprite.setPosition(position);
    update_position(position);
}

Projectile::Projectile(const ProjectileData &projectileData, sf::Vector2f position) :
        Collidable(projectileData.collision), sprite(*projectileData.texture), position(position),
        data(projectileData) {

}
