//
// Created by tobiasz on 17.05.2022.
//

#pragma once

#include <vector>
#include <string>

enum SHIP_TEXTURE {};

struct ShipData {

};

struct LevelData {
    std::string background;
    std::vector<ShipData> ships;
};