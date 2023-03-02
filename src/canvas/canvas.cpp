#include <canvas/canvas.h>

void CanvasElement::operator = (const CanvasElement &element)
{
    ch_ = element.ch_;
    color_ = element.color_;
}

Canvas::Canvas(int x, int y): x_(x), y_(y)
{
    if (x < 0 || y < 0)
    {
        x_ = 0;
        y_ = 0;
    }

    canvas_ = std::make_unique<std::unique_ptr<CanvasElement[]>[]>(x_);
    for (int i = 0; i < x_; ++i)
    {
        canvas_[i] = std::make_unique<CanvasElement[]>(y_);
        for (int j = 0; j < y_; ++j)
        {
            canvas_[i][j] = BLANK;
        }
    }

    ColorPrint_[RED] = RedPrint;
    ColorPrint_[GREEN] = GreenPrint;
    ColorPrint_[BLUE] = BluePrint;
    ColorPrint_[YELLOW] = YellowPrint;
    ColorPrint_[PURPLE] = PurplePrint;
    ColorPrint_[DARKGREEN] = DarkGreenPrint;
    ColorPrint_[BLACK] = BlackPrint;
}

Canvas::~Canvas()
{
    
}

void Canvas::CanvasSet(int x, int y, OBJECT::ObjectType element)
{
    if (x >= x_ || y >= y_ || x < 0 || y < 0)
    {
        return;
    }

    canvas_[x][y] = elements[element];
}

void Canvas::CanvasReset(int x, int y)
{
    CanvasSet(x, y, OBJECT::VOID);
}

inline void Canvas::ScreenClear() const
{
#if defined(__APPLE__) || defined(__linux__)
    system("clear");
#elif defined(_WIN64)
    system("cls");
#endif
}

void Canvas::CanvasPrint() const
{
    ScreenClear();
    for (int i = 0; i < x_; ++i)
    {
        for (int j = 0; j < y_; ++j)
        {
            (*(ColorPrint_[canvas_[i][j].color_]))(canvas_[i][j].ch_);
        }
        std::cout << std::endl;
    }
    // std::cout << "canvas print finished" << std::endl;
}
