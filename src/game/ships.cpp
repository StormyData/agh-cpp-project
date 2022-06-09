#include "ships.h"

#include <cmath>
#include <memory>
#include "level.h"
#include "projectile.h"
#include "enemy_ais.h"
#include "../system/context.h"


bool Ship::get_hit_by(const Projectile &projectile) {
    if (side == projectile.getSide())
        return false;
    if (!collides(projectile))
        return false;
    health--;
    hpBar.set_hp(health);
    if (health <= 0) {
        if (!is_dead) {
            level_ptr->add_effect(context.asset_loader.get_misc_config("ship_explosion_animation"),
                                  position + animation.getSize() / 2.0f);
            context.sound_engine.play_sound(context.asset_loader.get_misc_config("ship_explosion_sound"));
        }

        is_dead = true;
    }
    return true;
}


void Ship::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(animation, states);
    target.draw(hpBar, states);
}

void Ship::update(float dt) {
    wall_collision = {0, 0};
    sf::Vector2f max_position = (sf::Vector2f) context.window.getSize() - animation.getSize();
    position += dt * speed;
    if (position.x < 0) {
        position.x = 0;
        wall_collision.x = -1;
    } else if (position.x >= max_position.x) {
        position.x = max_position.x;
        wall_collision.x = 1;
    }
    if (position.y < 0) {
        position.y = 0;
        wall_collision.y = -1;
    } else if (position.y >= max_position.y) {
        position.y = max_position.y;
        wall_collision.y = 1;
    }
    animation.setPosition(position);
    animation.update(dt);
    hpBar.set_position(position);
    speed = {0.0f, 0.0f};
    update_position(position);
}

Ship::Ship(const ShipData *shipData, Side side, Context &context, Level *level) :
        Collidable(shipData->type.collision), health(shipData->hp),
        side(side), position(shipData->start_pos), animation(shipData->type.animation),
        context(context), level_ptr(level),
        hpBar(shipData->hp, shipData->type.hp_bar_offset + animation.getSize() / 2.0f),
        fired_projectiles(shipData->fired_projectiles) {}

void Ship::fire_projectiles() {
    for (auto &pair: fired_projectiles)
        level_ptr->add_projectile(new Projectile(pair.first, pair.second + position));
}

PlayerShip::PlayerShip(Level *level, const PlayerData *shipData, Context &context) :
        Ship(shipData, PLAYER, context, level), reset_timer(shipData->resetTimer) {

}

void PlayerShip::update(float dt) {
    handle_keyboard();
    Ship::update(dt);
    if (timer > 0) {
        timer -= dt;
        if (timer < 0)
            timer = 0;
    }
}

void PlayerShip::handle_keyboard() {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
        speed += {-speed_change, 0};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
        speed += {speed_change, 0};

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
        speed += {0, -speed_change};

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
        speed += {0, speed_change};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timer == 0) {
        timer = reset_timer;
        fire_projectiles();
    }
}

void EnemyShip::update(float dt) {
    Ship::update(dt);
    timer -= dt;
    if (timer < 0) {
        fire_projectiles();
        timer = context.enemy_random_distribution(context.random_engine);
    }
    speed += ai->update(dt, wall_collision);


}


EnemyShip::EnemyShip(const EnemyShipData *shipData, Context &context, Level *level) :
        Ship(shipData, ENEMY, context, level) {
    timer = context.enemy_random_distribution(context.random_engine);

    switch (shipData->ai_type) {
        case -1:
            ai = std::make_unique<LeftToRightAI>(context, true);
            break;
        case 1:
            ai = std::make_unique<LeftToRightAI>(context, false);
            break;
        case 2:
            ai = std::make_unique<StaticAI>();
            break;
        case 3:
            ai = std::make_unique<LeftToRightSinesAI>();
            break;
        case 4:
            ai = std::make_unique<LeftToRightSineSpeedUpDownCosAI>();
            break;
        case 5:
            ai = std::make_unique<MovingInCircleAI>();
            break;
        case 6:
            ai = std::make_unique<MovingInEightsAI>();
            break;
        case 7:
            ai = std::make_unique<DiagonallyMovingAI>();
            break;
        case 8:
            ai = std::make_unique<PolynomialMovingAI>();
            break;
        default:
            throw std::invalid_argument(std::string("unknown ai type: ") + std::to_string(shipData->ai_type));
    }
}
