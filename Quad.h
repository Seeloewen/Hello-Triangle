#pragma once

#include "Resolution.h"

struct Quad
{
	float x1, y1, x2, y2, x3, y3, x4, y4;

	Quad(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4) : x1(xToScreen(x1)), y1(yToScreen(y1)), x2(xToScreen(x2)), y2(yToScreen(y2)), x3(xToScreen(x3)), y3(yToScreen(y3)), x4(xToScreen(x4)), y4(yToScreen(y4)) {};
};