//
// Created by tobiasz on 23.05.2022.
//

#pragma once
#include "AssetLoader.h"

class SoundEngine {
public:
    explicit SoundEngine(AssetLoader& assetLoader): assetLoader(assetLoader) {};
    void play_sound(const std::string& name){std::cout << "playing sound: " << name << std::endl;};
    void play_music(const std::string& name) {std::cout << "playing music: " << name << std::endl;};
    void update(){};
    void reset(){};
private:
    AssetLoader& assetLoader;
    sf::Music music;
};


