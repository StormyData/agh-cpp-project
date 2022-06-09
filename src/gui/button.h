#pragma once

#include <SFML/Graphics.hpp>
#include <functional>
#include "../system/common.h"

class AssetLoader;

struct ButtonProperties {
    Alignment h_align;
    Alignment v_align;
    sf::FloatRect where;
    std::string text;
    std::function<void(void)> onClick;
};

class Button : public sf::Drawable {
    float text_to_cursor_distance = 5;
    sf::Text display_text;
    sf::Sprite cursors[2];
    sf::FloatRect rect;
    bool moused_over = false;
    std::function<void(void)> on_clicked;
    Alignment h_align = CENTER;
    Alignment v_align = CENTER;
public:
    Button() = default;;

    Button(const ButtonProperties &properties, const AssetLoader &assetLoader);

    bool test_mouseover(sf::Vector2f);

    bool test_click(sf::Vector2f);

    void draw(sf::RenderTarget &target, sf::RenderStates states) const override;

    void calc_positions(sf::FloatRect where);
};