#include "button.h"

#include "../system/asset_loader.h"


void Button::draw(sf::RenderTarget &target, sf::RenderStates states) const {
    target.draw(display_text, states);
    if (moused_over) {
        target.draw(cursors[0], states);
        target.draw(cursors[1], states);
    }

}

bool Button::test_mouseover(sf::Vector2f where) {
    bool old_state = moused_over;
    moused_over = rect.contains(where);
    return old_state != moused_over;
}

bool Button::test_click(sf::Vector2f where) {
    bool ret = rect.contains(where);
    if (ret) {
        on_clicked();
    }
    return ret;
}


Button::Button(const ButtonProperties &properties, const AssetLoader &assetLoader) : on_clicked(properties.onClick),
                                                                                     h_align(properties.h_align),
                                                                                     v_align(properties.v_align) {
    display_text.setString(properties.text);
    display_text.setFont(assetLoader.get_font());
    const sf::Texture &cursor_texture_ref = assetLoader.get_texture(
            assetLoader.get_misc_config("button_cursor_texture"));
    cursors[0].setTexture(cursor_texture_ref, true);
    cursors[1].setTexture(cursor_texture_ref, true);
    cursors[0].setScale(3, 3);
    cursors[1].setScale(-3, 3);

    calc_positions(properties.where);

}

void Button::calc_positions(sf::FloatRect where) {

    sf::FloatRect text_rect = display_text.getGlobalBounds();
    sf::Vector2f total_size(text_rect.width + text_rect.left, text_rect.height + text_rect.top);
    total_size.x += cursors[0].getGlobalBounds().width;
    total_size.x += cursors[1].getGlobalBounds().width;
    total_size.x += 2 * text_to_cursor_distance;
    total_size.y = std::max(total_size.y, cursors[0].getGlobalBounds().height);
    total_size.y = std::max(total_size.y, cursors[1].getGlobalBounds().height);
    sf::Vector2f pos = util::align(where, total_size,
                                   h_align, v_align);
    sf::Vector2f first_cursor_pos(0, 0);
    first_cursor_pos.x = pos.x;
    first_cursor_pos.y = pos.y + total_size.y / 2 - cursors[0].getGlobalBounds().height / 2;

    sf::Vector2f text_pos(0, 0);
    text_pos.x = pos.x + text_to_cursor_distance + cursors[0].getGlobalBounds().width - text_rect.left;
    text_pos.y = pos.y + total_size.y / 2 - text_rect.height / 2 - text_rect.top;

    sf::Vector2f second_cursor_pos(0, 0);
    second_cursor_pos.x = pos.x + total_size.x;
    second_cursor_pos.y = pos.y + total_size.y / 2 - cursors[1].getGlobalBounds().height / 2;

    cursors[0].setPosition(first_cursor_pos);
    cursors[1].setPosition(second_cursor_pos);
    display_text.setPosition(text_pos);
    rect = display_text.getGlobalBounds();
}
