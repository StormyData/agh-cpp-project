#pragma once

#include <SFML/Graphics.hpp>
#include <iostream>
#include <tinyxml2.h>
#include <unordered_map>
#include <SFML/Audio.hpp>
#include <functional>
#include "../gui/animation.h"
#include "../game/game_data.h"

class AssetLoader {

    std::unordered_map<std::string, sf::Texture *> textures{};
    std::unordered_map<std::string, AnimationData> animations{};
    std::unordered_map<std::string, CollisionData> collisions{};
    std::unordered_map<std::string, ProjectileData> projectile_types{};
    std::unordered_map<std::string, ShipType> ship_types{};
    std::unordered_map<std::string, EnemyShipData> enemy_ship_types{};
    std::unordered_map<std::string, SoundProperties> sounds;
    std::vector<LevelData> levels;
    std::unordered_map<std::string, displayText> strings;
    std::unordered_map<std::string, std::string> misc_config;
    std::unordered_map<std::string, MusicProperties> music;
    sf::Font font;
    PlayerData playerData;

    void load_texture(tinyxml2::XMLElement *element, std::string where);

    void load_anim(tinyxml2::XMLElement *element, std::string where);

    void load_projectile(tinyxml2::XMLElement *element, std::string where);

    void load_collision(tinyxml2::XMLElement *element, std::string where);

    void load_ship_type(tinyxml2::XMLElement *element, std::string where);

    void load_string(tinyxml2::XMLElement *element, std::string where);

    void load_levels(tinyxml2::XMLElement *element, std::string where);

    void load_level(tinyxml2::XMLElement *element, std::string where);

    void load_enemy_ship_data(tinyxml2::XMLElement *element, std::string where);

    void load_player_ship_data(tinyxml2::XMLElement *element, std::string where);

    void load_sound(tinyxml2::XMLElement *element, std::string where);

    void load_misc_config(tinyxml2::XMLElement *element, std::string where);

    void load_music(tinyxml2::XMLElement *element, std::string where);

    void load_file(const std::string &path);

    std::unordered_map<std::string, std::function<void(tinyxml2::XMLElement *, std::string)>> parse_functions{
            {"texture",          [this](auto &&PH1, auto &&PH2) {
                load_texture(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
            }},
            {"animation",        [this](auto &&PH1, auto &&PH2) {
                load_anim(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
            }},
            {"projectile",       [this](auto &&PH1, auto &&PH2) {
                load_projectile(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
            }},
            {"collision",        [this](auto &&PH1, auto &&PH2) {
                load_collision(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
            }},
            {"ship_type",        [this](auto &&PH1, auto &&PH2) {
                load_ship_type(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
            }},
            {"text",             [this](auto &&PH1, auto &&PH2) {
                load_string(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
            }},
            {"levels",           [this](auto &&PH1, auto &&PH2) {
                load_levels(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
            }},
            {"enemy_ship_data",  [this](auto &&PH1, auto &&PH2) {
                load_enemy_ship_data(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
            }},
            {"player_ship_data", [this](auto &&PH1, auto &&PH2) {
                load_player_ship_data(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
            }},
            {"sound",            [this](auto &&PH1, auto &&PH2) {
                load_sound(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
            }},
            {"misc_config",      [this](auto &&PH1, auto &&PH2) {
                load_misc_config(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
            }},
            {"music",            [this](auto &&PH1, auto &&PH2) {
                load_music(std::forward<decltype(PH1)>(PH1), std::forward<decltype(PH2)>(PH2));
            }}
    };
public:
    const sf::Texture &get_texture(const std::string &name) const {
        if (!textures.contains(name))
            throw std::invalid_argument("unknown texture name: " + name);
        return *textures.at(name);
    }

    const sf::Font &get_font() const {
        return font;
    }

    CollisionData get_collision(const std::string &name) const {
        if (!collisions.contains(name))
            throw std::invalid_argument("unknown collision name: " + name);
        return collisions.at(name);
    }


    displayText get_string(const std::string &name) const {
        if (!strings.contains(name))
            throw std::invalid_argument("unknown string name: " + name);
        return strings.at(name);
    }

    SoundProperties get_sound_buffer(const std::string &name) const {
        if (!sounds.contains(name))
            throw std::invalid_argument("unknown sound name: " + name);
        return sounds.at(name);
    }

    AssetLoader() {
        if (!font.loadFromFile("../assets/arial.ttf"))
            std::cout << "cannot load font";
        load_file("../assets/assets.xml");
    }

    ~AssetLoader() {
        std::for_each(textures.begin(), textures.end(), [](auto pair) { delete pair.second; });
        std::for_each(sounds.begin(), sounds.end(), [](auto pair) { delete pair.second.buffer; });
    }

    AnimationData get_animation(const std::string &name) {
        if (!animations.contains(name))
            throw std::invalid_argument("unknown animation name: " + name);
        return animations.at(name);
    }

    const std::vector<LevelData> &get_levels();

    const PlayerData &get_player_ship_data();

    const std::string &get_misc_config(const std::string &key) const {
        if (!misc_config.contains(key))
            throw std::invalid_argument("unknown misc config key: " + key);
        return misc_config.at(key);

    }

    MusicProperties get_music_properties(const std::string &name) {
        if (!music.contains(name))
            throw std::invalid_argument("unknown music pool name: " + name);
        return music.at(name);

    }

};