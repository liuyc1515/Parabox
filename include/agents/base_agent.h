#pragma once

#include <keyboard/keyboard_control.h>
#include <canvas/canvas.h>
#include <objects/base_object.h>
#include <maps/base_map.h>
#include <maps/static_maps/base_static_map.h>

class BaseAgent
{
private:
    Canvas canvas_;
    BaseMap *map_;
    int x_;
    int y_;
    virtual void UpdateCanvas();
public:
    BaseAgent(int canvas_x, int canvas_y, int op_x, int op_y);
    virtual ~BaseAgent();
    virtual void OperatorMove(ACTION::Action act);
};
