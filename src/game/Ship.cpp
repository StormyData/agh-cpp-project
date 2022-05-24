//
// Created by tobiasz on 17.05.2022.
//

#include "Ship.h"

bool Ship::get_hit_by(const Projectile &projectile) {
    if(side == projectile.getSide())
        return false;
    if(!colides(projectile))
        return false;
    health--;
    if(health<=0)
        is_dead = true;
    return true;
}

Ship::Ship(const ShipData &shipData, const AssetLoader &assetLoader): Collidable(shipData.type.colision), animation(shipData.type.animation) {
//TODO:
}

void Ship::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(animation, states);
}

void Ship::update(float dt) {

}
