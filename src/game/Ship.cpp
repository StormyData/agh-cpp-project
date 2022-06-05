//
// Created by tobiasz on 17.05.2022.
//

#include "Ship.h"
#include "Level.h"

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


void Ship::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(animation, states);
}

void Ship::update(float dt) {
    wall_colision = {0,0};
    sf::Vector2f max_position = (sf::Vector2f)context.window.getSize() - animation.getSize();
    position += dt * speed;
    if(position.x < 0)
    {
        position.x = 0;
        wall_colision.x = -1;
    } else if(position.x >= max_position.x)
    {
        position.x = max_position.x;
        wall_colision.x = 1;
    }
    if(position.y < 0)
    {
        position.y = 0;
        wall_colision.y = -1;
    } else if(position.y >= max_position.y)
    {
        position.y = max_position.y;
        wall_colision.y = 1;
    }
    animation.setPosition(position);
    animation.update(dt);
    update_position(position);
}

Ship::Ship(const ShipData &shipData, Context &context, Level* level):
    Collidable(shipData.type.colision), health(shipData.hp),
    position(shipData.start_pos), animation(shipData.type.animation), context(context),
    level_ptr(level), fired_projectiles(shipData.fired_projectiles){}

void Ship::fire_projectiles() {
    for(auto& pair : fired_projectiles)
        level_ptr->add_projectile(new Projectile(pair.first, pair.second + position));
}

PlayerShip::PlayerShip(Level *level, const PlayerData &shipData, Context &context) :
    Ship(shipData, context, level), reset_timer(shipData.resetTimer) {

}

void PlayerShip::update(float dt) {
    handle_keyboard(dt);
    Ship::update(dt);
    if(reset_timer > 0)
    {
        reset_timer -= dt;
        if(reset_timer < 0)
            reset_timer = 0;
    }
}

void PlayerShip::handle_keyboard(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        speed = {-speed_change, 0};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        speed = {speed_change, 0};

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        speed = {0, -speed_change};

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        speed = {0, speed_change};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || timer == 0)
    {
        timer = reset_timer;
        fire_projectiles();
    }
}
