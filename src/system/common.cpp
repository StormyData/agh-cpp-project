#include "common.h"

sf::Vector2f util::align(sf::FloatRect box, sf::Vector2f size, Alignment h_align, Alignment v_align) {
    sf::Vector2f box_center(box.left + box.width / 2, box.top + box.height / 2);
    sf::Vector2f pos(0, 0);

    switch (h_align) {
        case LOWER:
            pos.x = box.left;
            break;
        case CENTER:
            pos.x = box_center.x - size.x / 2;
            break;
        case HIGHER:
            pos.x = box.left + box.width - size.x;
            break;
    }

    switch (v_align) {
        case LOWER:
            pos.y = box.top;
            break;
        case CENTER:
            pos.y = box_center.y - size.y / 2;
            break;
        case HIGHER:
            pos.y = box.top + box.height - size.y;
            break;
    }
    return pos;
}
