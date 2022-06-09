#pragma once

#include <SFML/Window/Event.hpp>

struct Context;

class Screen {
public:
    explicit Screen(Context &context, bool wait) :
            context(context), wait(wait) {};

    virtual Screen *run();

protected:
    Context &context;

    virtual void on_enter() {};

    virtual bool process_additional_event(sf::Event &) = 0;

    virtual bool update_logic(float) = 0;

    virtual void draw() = 0;

    virtual void on_window_exit_pressed() { set_return(nullptr); }

    void set_return(Screen *screen) {
        retval = screen;
        should_return = true;
    }

private:
    Screen *retval = nullptr;
    bool should_return = false;
    bool wait;
};


