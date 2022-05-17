#include "AssetLoader.h"


void AssetLoader::load_texture(std::string name, std::string path) {
    if(!textures.contains(name))
    {
        textures[name] = new sf::Texture;
    }
    textures[name]->loadFromFile(path);
}
