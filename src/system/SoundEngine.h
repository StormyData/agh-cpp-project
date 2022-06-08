//
// Created by tobiasz on 23.05.2022.
//

#pragma once
#include "AssetLoader.h"
#include <list>
#include <utility>

class SoundEngine {
public:
    explicit SoundEngine(AssetLoader& assetLoader): assetLoader(assetLoader){}
    void play_sound(const std::string& name);
    void play_music(const std::string& name, bool restart = false);
    void update();
private:
    std::list<sf::Sound> sounds;
    AssetLoader& assetLoader;
    sf::Music music;
    std::string currently_playing_music_pool;
    MusicProperties current_music_properties;
    size_t current_index;
    void on_music_loop();
};


