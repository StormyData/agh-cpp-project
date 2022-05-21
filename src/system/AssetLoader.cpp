#include "AssetLoader.h"
#include <fstream>
#include <tinyxml2.h>
const tinyxml2::XMLAttribute* getAttrOrThrow(tinyxml2::XMLElement* element, const char* name)
{
    const tinyxml2::XMLAttribute* attr = element->FindAttribute(name);
    if(attr == nullptr)
        throw std::invalid_argument("element does not have required attribute");
    return attr;
}


void AssetLoader::load_texture(tinyxml2::XMLElement *element) {
    std::string texture_name = getAttrOrThrow(element,"name")->Value();
    std::string texture_path = getAttrOrThrow(element, "path")->Value();
    if(!textures.contains(texture_name))
    {
        textures[texture_name] = new sf::Texture;
    }
    textures[texture_name]->loadFromFile(texture_path);
}

void AssetLoader::load_anim(tinyxml2::XMLElement *element) {
    std::string anim_name = getAttrOrThrow(element,"name")->Value();
    std::string texture_name = getAttrOrThrow(element,"texture_name")->Value();

    AnimationData data;
    data.texture = &get_texture(texture_name);
    data.frames_in_row = getAttrOrThrow(element, "frames_in_row")->IntValue();
    data.frame_size.x = getAttrOrThrow(element, "frame_width")->IntValue();
    data.frame_size.y = getAttrOrThrow(element, "frame_height")->IntValue();
    int nframes = getAttrOrThrow(element,"nframes")->IntValue();
    data.times = std::vector<float>(nframes, 1.0);
    animations[anim_name] = data;
}

void AssetLoader::load_file(const std::string& path) {
    tinyxml2::XMLDocument doc;
    doc.LoadFile(path.c_str());
    tinyxml2::XMLElement* root = doc.FirstChildElement();
    if(std::string(root->Name()) != "assets")
        return;
    tinyxml2::XMLElement* element = root->FirstChildElement();
    while(element != nullptr)
    {
        std::string name = element->Name();
        if(name == "texture")
            load_texture(element);
        else if(name == "animation")
            load_anim(element);
        element = element->NextSiblingElement();
    }

}

