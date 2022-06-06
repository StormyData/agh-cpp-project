//
// Created by tobiasz on 17.05.2022.
//

#include "Ship.h"

#include <cmath>
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
    speed = {0.0f, 0.0f};
    update_position(position);
}

Ship::Ship(const ShipData* shipData, Side side, Context &context, Level* level):
    Collidable(shipData->type.colision), health(shipData->hp),
    side(side), position(shipData->start_pos), animation(shipData->type.animation),
    context(context), level_ptr(level), fired_projectiles(shipData->fired_projectiles){}

void Ship::fire_projectiles() {
    for(auto& pair : fired_projectiles)
        level_ptr->add_projectile(new Projectile(pair.first, pair.second + position));
}

PlayerShip::PlayerShip(Level *level, const PlayerData* shipData, Context &context) :
    Ship(shipData, PLAYER, context, level), reset_timer(shipData->resetTimer) {

}

void PlayerShip::update(float dt) {
    handle_keyboard(dt);
    Ship::update(dt);
    if(timer > 0)
    {
        timer -= dt;
        if(timer < 0)
            timer = 0;
    }
}

void PlayerShip::handle_keyboard(float dt) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        speed += {-speed_change, 0};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        speed += {speed_change, 0};

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        speed += {0, -speed_change};

    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        speed += {0, speed_change};
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) && timer == 0)
    {
        timer = reset_timer;
        fire_projectiles();
    }
}

void EnemyShip::update(float dt) {
    Ship::update(dt);
    timer -= dt;
    if(timer < 0)
    {
        fire_projectiles();
        timer = (*distribution)(context.randomEngine);
    }

    const float _baseSpeed = 60.0f;
    switch(ai_type)
    {
        case 1:
            if (wall_colision.x == 1 && _side == 1)
            {
                _side = 0;
            }

            if (wall_colision.x == -1 && _side == -1)
            {
                _side = 0;
            }
            if (_dist > context.window.getSize().y / 10)
            {
                _dist = 0;
                if (position.x < context.window.getSize().x / 2)
                    _side = 1;
                else
                    _side = -1;
            }
            switch (_side)
            {
                case 0:
                    speed += (sf::Vector2f (0, _baseSpeed));
                    _dist += 60 * dt;
                    break;
                case 1:
                    speed += sf::Vector2f (_baseSpeed, 0);
                    break;
                case -1:
                    speed += sf::Vector2f (_baseSpeed*-1, 0);
                    break;
                default:
                    break;
            }
            break;

        case 2:
            //static
            speed += (sf::Vector2f(0, 0));
            break;

        case 3:
            //sinu�
            if (wall_colision.x == 1 && _side == 1)
            {
                _side = -1;
            }
            if (wall_colision.x == -1 && _side == -1)
            {
                _side = 1;
            }
            speed += (sf::Vector2f(_baseSpeed*_side, std::sin(_aiVar) *60.0f));
            _aiVar += 0.01f * dt * 60;
            break;
        case 4:
            //left to right sin speed
            if (wall_colision.x == 1 && _side == 1)
            {
                _side = -1;
            }
            if (wall_colision.x == -1 && _side == -1)
            {
                _side = 1;
            }
            speed += (sf::Vector2f (fabsf(std::sin(_aiVar))* _side *1.5f *60.0f, std::cos(_aiVar) *60.0f));
            _aiVar += 0.01f * dt * 60;
            break;
        case 5:
            //circle
            speed += (sf::Vector2f (std::cos(_aiVar) * 60.0f, std::sin(_aiVar)  * 60.0f));
            _aiVar += 0.01f * dt * 60;
            break;
        case 6:
            //8
            speed += (sf::Vector2f (std::cos(_aiVar)  * 60.0f, std::cos(_aiVar*2)  * 60.0f));
            _aiVar += 0.01f * dt * 60;
            break;
        case 7:
            //diagonal variable speed
            speed += (sf::Vector2f (std::cos(_aiVar)  * 60.0f, std::cos(_aiVar)  * 60.0f));
            _aiVar += 0.02f * dt * 60;
            break;
        case 8:
            //polynomial
            if (wall_colision.x == 1 && _side == 1)
            {
                _side = -1;
            }
            if (wall_colision.x == -1 && _side == -1)
            {
                _side = 1;
            }
            speed += (sf::Vector2f ((_aiVar + 2)*(_aiVar + 1)*(_aiVar - 0.5)*(_aiVar - 1.5)*_side *60.0f, std::cos(_aiVar2) *60.0f));
            _aiVar += 0.01f * dt * 60;
            _aiVar2 += 0.01f * dt * 60;
            if (_aiVar > 1.9)
                _aiVar = -2.3f;
            break;
        default:
            if (wall_colision.x == 1)
            {
                speed += (sf::Vector2f (_baseSpeed*-1, 0));
            }

            if (wall_colision.x == -1)
            {
                speed += (sf::Vector2f (_baseSpeed*-1, 0));
            }
            break;
    }


}
std::normal_distribution<float>* EnemyShip::distribution = new std::normal_distribution(0.8306567833333334f, 0.04800254879908575f);

EnemyShip::EnemyShip(const EnemyShipData* shipData, Context &context, Level* level):
Ship(shipData, ENEMY, context, level), ai_type(shipData->ai_type)
{
    timer = (*distribution)(context.randomEngine);
    if (ai_type == -1)
    {
        _side = -1;
        ai_type = 1;
    }

}
