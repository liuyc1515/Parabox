#pragma once

#include <thread>
#include <mutex>

#include <keyboard/keyboard_control.h>
#include <agents/base_agent.h>
#include <canvas/canvas.h>
#include <manager/object_manager.h>

class Parabox
{
private:
    KeyboardControl keyboard_;
    BaseAgent agent_;
    Canvas canvas_;
    std::shared_ptr<const ObjectManager> object_manager_;
    void UpdateCanvas();
public:
    Parabox();
    void Start();
};
