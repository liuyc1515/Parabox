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

	COLOR_COUNT
};

enum ElementEffect {
	NOEFFECT = 0,
	UNDERLINE0,

	EFFECT_COUNT
};

struct CanvasElement {
		char ch_;
		ElementColor color_;
		ElementEffect effect_;
		void operator=(const CanvasElement &element);
};

const CanvasElement BLANK = {' ', BLACK, NOEFFECT};
const CanvasElement WALL = {'W', WHITE, NOEFFECT};
const CanvasElement OPERATOR = {'P', YELLOW, NOEFFECT};
const CanvasElement BLOCK = {'B', GREEN, NOEFFECT};
const CanvasElement INNER = {'M', PURPLE, NOEFFECT};
const CanvasElement RECURSION = {'R', DARKGREEN, NOEFFECT};

const CanvasElement elements[OBJECT::OBJ_COUNT] = {BLANK, WALL, OPERATOR, BLOCK, INNER, RECURSION};

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
