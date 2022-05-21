#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "../gui/Animation.h"
#include <tinyxml2.h>
class AssetLoader
{

    std::unordered_map<std::string, sf::Texture*> textures;
    std::unordered_map<std::string, AnimationData> animations;
    sf::Font font;

    void load_texture(tinyxml2::XMLElement *element);
    void load_anim(tinyxml2::XMLElement *element);
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
};