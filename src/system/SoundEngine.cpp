//
// Created by tobiasz on 23.05.2022.
//

#include "SoundEngine.h"

void SoundEngine::play_sound(const std::string &name) {
    // std::cout << "playing sound: " << name << std::endl;
    SoundProperties properties = assetLoader.get_sound_buffer(name);
    sounds.emplace_back(*properties.buffer);
    sounds.back().setVolume(properties.volume);
    sounds.back().play();
}

void SoundEngine::update() {
    sounds.remove_if([](const sf::Sound& sound){return sound.getStatus() == sf::Sound::Stopped;});
}

void SoundEngine::play_music(const std::string &name, bool restart) {
    if(currently_playing_music_pool == name && !restart)
        return;
    currently_playing_music_pool = name;
    current_index = -1;
    current_music_properties = assetLoader.get_music_properties(name);
    on_music_loop();
}

void SoundEngine::on_music_loop() {
    if(current_music_properties.files_with_volumes.empty())
    {
        music.stop();
        return;
    }
    current_index += 1;
    if(current_index >= current_music_properties.files_with_volumes.size())
        current_index = 0;
    music.openFromFile(current_music_properties.files_with_volumes[current_index].first);
    music.setVolume(current_music_properties.files_with_volumes[current_index].second);
    music.play();
}
