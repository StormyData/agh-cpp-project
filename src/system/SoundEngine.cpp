//
// Created by tobiasz on 23.05.2022.
//

#include "SoundEngine.h"

void SoundEngine::play_sound(const std::string &name) {
    // std::cout << "playing sound: " << name << std::endl;
    sounds.emplace_back(*assetLoader.get_sound_buffer(name));
    sounds.back().setVolume(12);
    sounds.back().play();
}

void SoundEngine::update() {
    sounds.remove_if([](const sf::Sound& sound){return sound.getStatus() == sf::Sound::Stopped;});
}
