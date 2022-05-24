//
// Created by tobiasz on 24.05.2022.
//

#pragma once
#include "../system/context.h"

class Screen {
public:
    explicit Screen(Context& context): context(context) {};
    virtual Screen* run();
protected:
    Context& context;
    virtual bool process_additional_event(sf::Event&) = 0;
    virtual bool update_logic(float) = 0;
    virtual void draw() = 0;
    virtual void on_exit(){ set_return(nullptr);}
    void set_return(Screen* screen){ retval = screen; should_return = true;}
private:
    Screen* retval = nullptr;
    bool should_return = false;

};


