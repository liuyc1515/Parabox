#pragma once

#include <canvas/color_print.h>
#include <utils/types.h>

enum ElementColor
{
    RED = 0,
    GREEN,
    BLUE,
    YELLOW,
    PURPLE,
    DARKGREEN,
    BLACK,
    WHITE,

    COLOR_COUNT
};

struct CanvasElement
{
    char ch_;
    ElementColor color_;
    void operator = (const CanvasElement & element);
};

const CanvasElement BLANK = {' ', BLACK};
const CanvasElement WALL = {'W', WHITE};
const CanvasElement OPERATOR = {'P', YELLOW};
const CanvasElement BLOCK = {'B', GREEN};

const CanvasElement elements[OBJECT::OBJ_COUNT] = {BLANK, WALL, OPERATOR, BLOCK};

class Canvas
{
private:
    int x_;
    int y_;
    std::unique_ptr<std::unique_ptr<CanvasElement[]>[]> canvas_;
    void(* ColorPrint_[COLOR_COUNT])(char);
public:
    /*
     * x from left to right
     * y from high to low
     */
    Canvas(int x, int y);
    ~Canvas();
    void CanvasSet(int x, int y, OBJECT::ObjectType element);
    void CanvasReset(int x, int y);
    inline void ScreenClear() const;
    void CanvasPrint() const;
    int GetCanvasX() const;
    int GetCanvasY() const;
};
