#pragma once

#include <vector>
#include <string>
#include <SFML/System/Vector2.hpp>
#include <SFML/Audio.hpp>
#include "../gui/animation.h"

enum Side {
    PLAYER, ENEMY
};


struct CollisionData {
    std::vector<sf::Vector2f> points;
};
struct ProjectileData {
    Side side = ENEMY;
    const sf::Texture *texture = nullptr;
    CollisionData collision;
    sf::Vector2f speed;
    std::string firing_sound_name;
};

struct ShipType {
    CollisionData collision;
    AnimationData animation;
    sf::Vector2f hp_bar_offset;
};

struct displayText {
    std::string text;
    unsigned int size;
    unsigned int style;
};

struct ShipData {
    ShipType type;
    int hp;
    std::vector<std::pair<ProjectileData, sf::Vector2f>> fired_projectiles;
    sf::Vector2f start_pos;
};
struct EnemyShipData : public ShipData {
    int ai_type = 0;
};

struct PlayerData : public ShipData {
    float resetTimer = 0;
};

struct LevelData {
    std::string background;
    std::vector<EnemyShipData> ships;
    std::string display_name;
    unsigned int next_level_no;
};

struct SoundProperties {
    sf::SoundBuffer *buffer;
    float volume;
};
struct MusicProperties {
    std::vector<std::pair<std::string, float>> files_with_volumes;
};