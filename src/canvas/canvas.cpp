#include <canvas/canvas.h>
#include "canvas/color_print.h"

void (*Canvas::ColorPrint_[COLOR_COUNT])(char);

void CanvasElement::operator=(const CanvasElement &element) {
	ch_ = element.ch_;
	color_ = element.color_;
	effect_ = element.effect_;
}

Canvas::Canvas(int x, int y) : x_(x), y_(y) {
	std::cout << "start init canvas with x : " << x_ << " and y : " << y_ << std::endl;

	if (x < 0 || y < 0) {
		x_ = 0;
		y_ = 0;
	}

	canvas_ = std::move(std::make_unique<std::unique_ptr<CanvasElement[]>[]>(x_));
	for (int i = 0; i < x_; ++i) {
		canvas_[i] = std::move(std::make_unique<CanvasElement[]>(y_));
		for (int j = 0; j < y_; ++j) {
			canvas_[i][j] = BLANK;
		}
	}
}

Canvas::Canvas() {
	InitCanvas(0, 0);
}

Canvas::~Canvas() {
}

void Canvas::InitCanvas(int x, int y) {
	std::cout << "start init canvas with x " << x << ", y " << y << std::endl;
	if (x_ == x && y_ == y) {
		return;
	}

	if (x < 0 || y < 0) {
		x_ = 0;
		y_ = 0;
	}

	SetCanvasX(x);
	SetCanvasY(y);

	canvas_ = std::move(std::make_unique<std::unique_ptr<CanvasElement[]>[]>(x_));
	for (int i = 0; i < x_; ++i) {
		canvas_[i] = std::move(std::make_unique<CanvasElement[]>(y_));
		for (int j = 0; j < y_; ++j) {
			canvas_[i][j] = BLANK;
		}
	}
}

void Canvas::SetCanvasX(int x) {
	x_ = x;
}

void Canvas::SetCanvasY(int y) {
	y_ = y;
}

void Canvas::InitColors() {
	ColorPrint_[RED] = RedPrint;
	ColorPrint_[GREEN] = GreenPrint;
	ColorPrint_[BLUE] = BluePrint;
	ColorPrint_[YELLOW] = YellowPrint;
	ColorPrint_[PURPLE] = PurplePrint;
	ColorPrint_[DARKGREEN] = DarkGreenPrint;
	ColorPrint_[BLACK] = BlackPrint;
	ColorPrint_[WHITE] = WhitePrint;
}

void Canvas::CanvasSet(const Coordinate &coord, OBJECT::ObjectType element) {
	if (coord.first >= x_ || coord.second >= y_ || coord.first < 0 || coord.second < 0) {
		return;
	}

	canvas_[coord.first][coord.second] = elements[element];
	// std::cout << "finished set canvas" << std::endl;
}

void Canvas::CanvasReset(const Coordinate &coord) {
	CanvasSet(coord, OBJECT::VOID);
}

inline void Canvas::ScreenClear() const {
#if defined(__APPLE__) || defined(__linux__)
	system("clear");
#elif defined(_WIN64)
	system("cls");
#endif
}

void Canvas::CanvasPrint() const {
	std::cout << "start print canvas" << std::endl;
	ScreenClear();
	for (int i = 0; i < x_; ++i) {
		for (int j = 0; j < y_; ++j) {
			(*(ColorPrint_[canvas_[i][j].color_]))(canvas_[i][j].ch_);
		}
		std::cout << std::endl;
	}
	// std::cout << "canvas print finished" << std::endl;
}

int Canvas::GetCanvasX() const {
	return x_;
}

int Canvas::GetCanvasY() const {
	return y_;
}
