#pragma once

#include <canvas/color_print.h>
#include <utils/types.h>

#include <map>
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
	UNDERLINE,

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

const std::map<ElementColor, int> printed_colors = {{BLACK, 30}, {RED, 31},	   {GREEN, 32},		{YELLOW, 33},
													{BLUE, 34},	 {PURPLE, 35}, {DARKGREEN, 36}, {WHITE, 37}};

const std::map<ElementEffect, int> printed_effects = {{NOEFFECT, 0}, {UNDERLINE, 4}};

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
		void CanvasSet(const Coordinate &coord, OBJECT::ObjectType type, OBJECT::ObjectStatus status);
		void CanvasReset(const Coordinate &coord);
		inline void ScreenClear() const;
		void CanvasPrint() const;
		int GetCanvasX() const;
		int GetCanvasY() const;
};
