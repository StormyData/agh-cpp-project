//
// Created by tobiasz on 23.05.2022.
//

#pragma once
#include "AssetLoader.h"
#include <list>
#include <utility>
class CallOnLoopMusic: public sf::Music
{
public:
    explicit CallOnLoopMusic(std::function<void()> on_loop_hook): on_loop(std::move(on_loop_hook)) {}
    sf::Int64 onLoop() override {on_loop(); return -1;}

private:
    std::function<void()> on_loop;
};

class SoundEngine {
public:
    explicit SoundEngine(AssetLoader& assetLoader): assetLoader(assetLoader), music([this](){this->on_music_loop();}) {}
    void play_sound(const std::string& name);
    void play_music(const std::string& name, bool restart = false);
    void update();
private:
    std::list<sf::Sound> sounds;
    AssetLoader& assetLoader;
    CallOnLoopMusic music;
    std::string currently_playing_music_pool;
    MusicProperties current_music_properties;
    size_t current_index;
    void on_music_loop();
};


