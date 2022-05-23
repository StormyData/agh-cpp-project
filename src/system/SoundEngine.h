//
// Created by tobiasz on 23.05.2022.
//

#pragma once
#include "AssetLoader.h"

class SoundEngine {
public:
    explicit SoundEngine(AssetLoader& assetLoader): assetLoader(assetLoader) {};
    void play_sound(const std::string& name);
    void play_music(const std::string& name);
    void update();
    void reset();
private:
    AssetLoader& assetLoader;
};


