#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

class AssetLoader
{
    std::vector<std::pair<std::string, std::string>> names{{"cursor", "../assets/img/cursor.png"},
                                                           {"main_menu_background", "../assets/img/bg_menu.png"}};

    std::unordered_map<std::string, sf::Texture*> textures;
    sf::Font font;

    void load_texture(std::string name, std::string path);

public:
    const sf::Texture& get_texture(const std::string& name) const
    {
        if(!textures.contains(name))
            ;
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
        for(auto & name : names)
        {
            load_texture(name.first, name.second);
        }

    }
    ~AssetLoader()
    {
        for(auto & texture : textures)
        {
            delete texture.second;
        }
    }
};