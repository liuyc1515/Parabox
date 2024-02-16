#pragma once

#include <canvas/color_print.h>
#include <utils/types.h>

#include <memory>

enum ElementColor {
	RED = 0,
	GREEN,
	BLUE,
	YELLOW,
	PURPLE,
	DARKGREEN,
	BLACK,
	WHITE,
	UNDERLINE,

	COLOR_COUNT
};

struct CanvasElement {
		char ch_;
		ElementColor color_;
		void operator=(const CanvasElement &element);
};

const CanvasElement BLANK = {' ', BLACK};
const CanvasElement WALL = {'W', WHITE};
const CanvasElement OPERATOR = {'P', YELLOW};
const CanvasElement BLOCK = {'B', GREEN};
const CanvasElement INNER = {'M', PURPLE};
const CanvasElement RECURSION = {'R', DARKGREEN};
const CanvasElement TARGET = {' ', UNDERLINE};

const CanvasElement elements[OBJECT::OBJ_COUNT] = {BLANK, WALL, OPERATOR, BLOCK, INNER, RECURSION, TARGET};

class Canvas {
	private:
		int x_;
		int y_;
		std::unique_ptr<std::unique_ptr<CanvasElement[]>[]> canvas_;
		static void (*ColorPrint_[COLOR_COUNT])(char);
		void SetCanvasX(int x);
		void SetCanvasY(int y);

	public:
		/*
		 * x from high to low
		 * y from left to right
		 */
		Canvas(int x, int y);
		Canvas();
		~Canvas();
		static void InitColors();
		void InitCanvas(int x, int y);
		void CanvasSet(const Coordinate &coord, OBJECT::ObjectType element);
		void CanvasReset(const Coordinate &coord);
		inline void ScreenClear() const;
		void CanvasPrint() const;
		int GetCanvasX() const;
		int GetCanvasY() const;
};
