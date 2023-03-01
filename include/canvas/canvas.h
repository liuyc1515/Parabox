#pragma once

#include <canvas/color_print.h>
#include <objects/object_types.h>

enum ElementColor
{
    RED = 0,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE,
    DARKGREEN,
    BLACK,

    COLOR_COUNT
};

struct CanvasElement
{
    char ch_;
    ElementColor color_;
    void operator = (const CanvasElement & element);
};

const CanvasElement BLANK = {' ', BLACK};
const CanvasElement WALL = {'W', RED};
const CanvasElement OPERATOR = {'P', YELLOW};
const CanvasElement BLOCK = {'B', GREEN};

const CanvasElement elements[OBJECT::OBJ_COUNT] = {BLANK, WALL, OPERATOR, BLOCK};

class Canvas
{
private:
    int x_;
    int y_;
    CanvasElement** canvas_;
    void(* ColorPrint_[COLOR_COUNT])(char);
public:
    /*
     * x from left to right
     * y from high to low
     */
    Canvas(int x, int y);
    Canvas(int x, int y, const CanvasElement** canvas);
    ~Canvas();
    void CanvasSet(int x, int y, OBJECT::ObjectType element);
    void CanvasReset(int x, int y);
    inline void ScreenClear() const;
    void CanvasPrint() const;
};
