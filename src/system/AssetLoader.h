#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../gui/Animation.h"
#include <tinyxml2.h>
#include <unordered_map>
#include "../game/GameData.h"
#include <SFML/Audio.hpp>
class AssetLoader
{

    std::unordered_map<std::string, sf::Texture*> textures{};
    std::unordered_map<std::string, AnimationData> animations{};
    std::unordered_map<std::string, ColisionData> colisions{};
    std::unordered_map<std::string, ProjectileData> projectile_types{};
    std::unordered_map<std::string, ShipType> ship_types{};
    std::vector<LevelData> levels;
    std::unordered_map<std::string, displayText> strings;
    sf::Font font;

    void load_texture(tinyxml2::XMLElement *element, std::string where);
    void load_anim(tinyxml2::XMLElement *element, std::string where);
    void load_projectile(tinyxml2::XMLElement *element, std::string where);
    void load_colision(tinyxml2::XMLElement* element, std::string where);
    void load_ship_type(tinyxml2::XMLElement* element, std::string where);
    void load_string(tinyxml2::XMLElement* element, std::string where);
    void load_file(const std::string& path);
public:
    const sf::Texture& get_texture(const std::string& name) const
    {
        if(!textures.contains(name))
            throw std::invalid_argument("unknown texture name: " + name);
        return *textures.at(name);
    }
    const sf::Font& get_font() const
    {
        return font;
    }
    ColisionData get_colision(const std::string& name) const
    {
        if(!colisions.contains(name))
            throw std::invalid_argument("unknown colision name: " + name);
        return colisions.at(name);
    }
    ProjectileData get_projectile_data(const std::string& name) const
    {
        if(!projectile_types.contains(name))
            throw std::invalid_argument("unknown projectile data name: " + name);
        return projectile_types.at(name);
    }
    displayText get_string(const std::string& name) const
    {
        if(!strings.contains(name))
            throw std::invalid_argument("unknown string name: " + name);
        return strings.at(name);
    }
    AssetLoader()
    {
        if(!font.loadFromFile("/usr/share/fonts/liberation/LiberationMono-Regular.ttf"))
            std::cout<< "cannot load font";
        load_file("../assets/assets.xml");
    }
    ~AssetLoader()
    {
        for(auto & texture : textures)
        {
            delete texture.second;
        }
    }

    AnimationData get_animation(const std::string &name)
    {
        if(!animations.contains(name))
            throw std::invalid_argument("unknown animation name: " + name);
        return animations.at(name);
    }

    const std::vector<LevelData> &get_levels();
};