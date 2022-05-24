//
// Created by tobiasz on 24.05.2022.
//

#include "Screen.h"

Screen* Screen::run() {
    sf::Clock clock1;
    bool redraw_required = false;
    while (context.window.isOpen())
    {
        float elapsed = (float)clock1.getElapsedTime().asMicroseconds() / 1000000.0f;
        clock1.restart();
        sf::Event event{};
        while (context.window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                on_exit();
            redraw_required |= process_additional_event(event);
        }

        redraw_required |= update_logic(elapsed);

        if(!redraw_required)
            continue;
        context.window.clear();
        draw();
        context.window.display();
        redraw_required = false;
        if(should_return)
            return retval;
    }
    return nullptr;
}
