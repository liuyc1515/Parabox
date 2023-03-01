#pragma once

#include <thread>
#include <mutex>

#include <keyboard/keyboard_control.h>
#include <agents/base_agent.h>

class Parabox
{
private:
    KeyboardControl keyboard_;
    BaseAgent agent_;
public:
    Parabox(int canvas_x, int canvas_y, int op_x, int op_y);
    void Start();
};
