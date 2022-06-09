#pragma once

#include <list>
#include <utility>
#include <SFML/Audio.hpp>
#include "../game/game_data.h"

class AssetLoader;

class SoundEngine {
public:
    explicit SoundEngine(AssetLoader &assetLoader) : assetLoader(assetLoader) {}

    void play_sound(const std::string &name);

    void play_music(const std::string &name, bool restart = false);

    void update();

private:
    std::list<sf::Sound> sounds;
    AssetLoader &assetLoader;
    sf::Music music;
    std::string currently_playing_music_pool;
    MusicProperties current_music_properties;
    size_t current_index = 0;

    void on_music_loop();
};


