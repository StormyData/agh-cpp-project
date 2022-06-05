#include "AssetLoader.h"
#include <fstream>
#include <tinyxml2.h>

const tinyxml2::XMLAttribute *
get_attribute_or_throw(tinyxml2::XMLElement *element, const char *name, const std::string &where = "") {
    const tinyxml2::XMLAttribute *attr = element->FindAttribute(name);
    if (attr == nullptr)
        throw std::invalid_argument(where + "{" + name + "} does not exist\n");
    return attr;
}

Side parse_side(const std::string &s, const std::string &where = "") {
    if (s == "enemy")
        return ENEMY;
    else if (s == "player")
        return PLAYER;
    throw std::invalid_argument(s + " in " + where + "is not a valid side");
}

sf::Vector2f parse_point(const std::string &s, const std::string &where = "") {
    size_t off = s.find(',');
    if (off == std::string::npos) {
        throw std::invalid_argument("invalid point literal" + s + " in " + where);
    }
    char* end;

    std::string tmp = s.substr(0, off);
    float x = std::strtof(tmp.c_str(), &end);
    if(end == tmp.c_str())
        throw std::invalid_argument("invalid point literal" + s + " (cannot parse " + tmp + ") in " + where);

    tmp = s.substr(off + 1, s.size() - off - 1);
    float y = std::strtof(tmp.c_str(), &end);
    if(end == tmp.c_str())
        throw std::invalid_argument("invalid point literal" + s + + " (cannot parse " + tmp + ") in " + where);

    return {x, y};
}


void AssetLoader::load_texture(tinyxml2::XMLElement *element, std::string where) {
    where += "::texture";
    std::string texture_name = get_attribute_or_throw(element, "name", where)->Value();
    where += "(" + texture_name + ")";
    std::string texture_path = get_attribute_or_throw(element, "path", where)->Value();
    if (!textures.contains(texture_name)) {
        textures[texture_name] = new sf::Texture;
    }
    textures[texture_name]->loadFromFile(texture_path);
}

void AssetLoader::load_anim(tinyxml2::XMLElement *element, std::string where) {
    where += "::animation";
    std::string anim_name = get_attribute_or_throw(element, "name", where)->Value();
    where += "(" + anim_name + ")";
    std::string texture_name = get_attribute_or_throw(element, "texture_name", where)->Value();

    AnimationData data;
    data.texture = &get_texture(texture_name);
    data.frames_in_row = get_attribute_or_throw(element, "frames_in_row", where)->IntValue();
    data.frame_size.x = get_attribute_or_throw(element, "frame_width", where)->IntValue();
    data.frame_size.y = get_attribute_or_throw(element, "frame_height", where)->IntValue();
    int nframes = get_attribute_or_throw(element, "nframes", where)->IntValue();
    data.times = std::vector<float>(nframes, 1.0 / 30);
    animations[anim_name] = data;
}

void AssetLoader::load_file(const std::string &path) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());
    tinyxml2::XMLElement *root = doc.FirstChildElement();
    if (std::string(root->Name()) != "assets")
        return;
    tinyxml2::XMLElement *element = root->FirstChildElement();
    while (element != nullptr) {
        std::string name = element->Name();
        if (name == "texture")
            load_texture(element, "assets");
        else if (name == "animation")
            load_anim(element, "assets");
        else if (name == "projectile")
            load_projectile(element, "assets");
        else if (name == "colision")
            load_colision(element, "assets");
        else if (name == "ship_type")
            load_ship_type(element, "assets");
        else if (name == "text")
            load_string(element, "assets");
        else if (name == "levels")
            load_levels(element, "assets");
        else if(name == "enemy_ship_data")
            load_enemy_ship_data(element, "assets");
        element = element->NextSiblingElement();
    }

}

void AssetLoader::load_projectile(tinyxml2::XMLElement *element, std::string where) {
    where += "::projectile";
    std::string name = get_attribute_or_throw(element, "name", where)->Value();
    where += "(" + name + ")";
    std::string texture_name = get_attribute_or_throw(element, "texture", where)->Value();
    std::string colision_name = get_attribute_or_throw(element, "colision", where)->Value();
    Side side = parse_side(get_attribute_or_throw(element, "side", where)->Value(), where + "{side}");
    sf::Vector2f speed = parse_point(get_attribute_or_throw(element, "speed", where)->Value(), where + "{speed}");
    projectile_types[name] = ProjectileData();
    projectile_types[name].side = side;
    projectile_types[name].colision = get_colision(colision_name);
    projectile_types[name].texture = &get_texture(texture_name);
    projectile_types[name].speed = speed;
}

void AssetLoader::load_ship_type(tinyxml2::XMLElement *element, std::string where) {
    where += "::ship_type";
    std::string name = get_attribute_or_throw(element, "name", where)->Value();
    where += "(" + name + ")";
    std::string animation_name = get_attribute_or_throw(element, "animation", where)->Value();
    std::string colision_name = get_attribute_or_throw(element, "colision", where)->Value();
    ship_types[name] = ShipType();
    ship_types[name].colision = get_colision(colision_name);
    ship_types[name].animation = get_animation(animation_name);
}

void AssetLoader::load_colision(tinyxml2::XMLElement *element, std::string where) {
    where += "::colision";
    std::string name = get_attribute_or_throw(element, "name", where)->Value();
    where += "(" + name + ")";
    colisions[name] = ColisionData();
    std::vector<sf::Vector2f> &data = colisions[name].points;
    tinyxml2::XMLElement *child = element->FirstChildElement();
    int i = 0;
    while (child != nullptr) {
        if (child->Name() == std::string("p")) {
            std::string p_where = where + ":[" + std::to_string(i) + "]:p";
            std::string p_str = get_attribute_or_throw(child, "pos", p_where)->Value();
            data.push_back(parse_point(p_str, p_where));
        }
        i++;
        child = child->NextSiblingElement();
    }
}

const std::vector<LevelData> &AssetLoader::get_levels() {
    return levels;
}

void AssetLoader::load_string(tinyxml2::XMLElement *element, std::string where) {
    where += "::text";
    std::string name = get_attribute_or_throw(element, "name", where)->Value();
    where += "(" + name + ")";
    unsigned int size = get_attribute_or_throw(element, "size", where)->UnsignedValue();
    unsigned int style = 0;
    if (element->QueryAttribute("style", &style) == tinyxml2::XML_NO_ATTRIBUTE)
        style = 0;
    where += "(" + name + ")";
    strings[name] = displayText();
    strings[name].text = element->GetText();
    strings[name].size = size;
    strings[name].style = style;

}

void AssetLoader::load_level(tinyxml2::XMLElement *element, std::string where) {
    where += "::level";
    LevelData data;
    data.display_name = get_attribute_or_throw(element, "display_name", where)->Value();
    where += "(" + data.display_name + ")";
    data.background = get_attribute_or_throw(element, "background", where)->Value();
    tinyxml2::XMLElement *child = element->FirstChildElement();
    int i=0;
    while (child != nullptr) {
        if (child->Name() == std::string("enemy"))
        {
            std::string e_where = where + "[" + std::to_string(i) + "]";
            std::string name = get_attribute_or_throw(child, "name", e_where)->Value();
            EnemyShipData enemy_data = enemy_ship_types[name];
            enemy_data.start_pos = parse_point(get_attribute_or_throw(child, "start_pos", e_where)->Value(), where);

            data.ships.push_back(enemy_data);
        }

        child = child->NextSiblingElement();
        i++;
    }

    data.next_level_no = levels.size() + 1;
    levels.push_back(data);
}

void AssetLoader::load_levels(tinyxml2::XMLElement *element, std::string where) {
    where += "::levels";
    tinyxml2::XMLElement *child = element->FirstChildElement();
    while (child != nullptr) {
        if (child->Name() == std::string("level")) {
            load_level(child, where);
        }
        child = child->NextSiblingElement();
    }

}

void AssetLoader::load_enemy_ship_data(tinyxml2::XMLElement *element, std::string where) {
    where += "::enemy_ship_data";
    std::string name = get_attribute_or_throw(element, "name", where)->Value();
    where += "(" + name + ")";
    std::string ship_type = get_attribute_or_throw(element, "ship_type", where)->Value();
    int ai_type = get_attribute_or_throw(element, "ai_type", where)->IntValue();
    int hp = get_attribute_or_throw(element, "hp", where)->IntValue();
    EnemyShipData data;
    tinyxml2::XMLElement *child = element->FirstChildElement();
    int i = 0;
    while (child != nullptr) {
        if (child->Name() == std::string("fired_projectile")) {
            std::string p_where = where + "[" + std::to_string(i) + "]::fired_projectile";
            std::string type = get_attribute_or_throw(child, "projectile_type", p_where)->Value();
            sf::Vector2f offset = parse_point(get_attribute_or_throw(child, "pos", p_where)->Value(), p_where);
            data.fired_projectiles.emplace_back(projectile_types[type], offset);
        }
        child = child->NextSiblingElement();
        i++;
    }
    data.ai_type = ai_type;
    data.start_pos = {0,0};
    data.type = ship_types[ship_type];
    data.hp = hp;
    enemy_ship_types[name] = data;
}

