//
// Created by tobiasz on 23.05.2022.
//

#pragma once
#include <SFML/Graphics.hpp>
#include <random>
#include "AssetLoader.h"
#include "SoundEngine.h"

struct Context
{
    sf::RenderWindow& window;
    AssetLoader assetLoader;
    SoundEngine soundEngine;
    std::default_random_engine randomEngine;
    explicit Context(sf::RenderWindow& window) : window(window),assetLoader(), soundEngine(assetLoader)
    {
    }
};