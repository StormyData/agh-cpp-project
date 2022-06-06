//
// Created by tobiasz on 23.05.2022.
//

#pragma once
#include "AssetLoader.h"
#include <list>

class SoundEngine {
public:
    explicit SoundEngine(AssetLoader& assetLoader): assetLoader(assetLoader) {};
    void play_sound(const std::string& name);
    void play_music(const std::string& name) {std::cout << "playing music: " << name << std::endl;};
    void update();
    void reset(){};
private:
    std::list<sf::Sound> sounds;
    AssetLoader& assetLoader;
    sf::Music music;
};


