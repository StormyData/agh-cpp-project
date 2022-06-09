#pragma once

#include <SFML/Graphics.hpp>
#include <random>
#include <chrono>
#include "asset_loader.h"
#include "sound_engine.h"

struct Context {
    sf::RenderWindow &window;
    AssetLoader asset_loader;
    SoundEngine sound_engine;
    std::default_random_engine random_engine;
    std::normal_distribution<float> enemy_random_distribution;

    explicit Context(sf::RenderWindow &window) :
            window(window), asset_loader(), sound_engine(asset_loader),
            random_engine(std::chrono::system_clock::now().time_since_epoch().count()),
            enemy_random_distribution(0.8306567833333334f, 0.04800254879908575f) {
    }
};