#pragma once

#include "Resolution.h"

struct Triangle
{
	float x1, y1, x2, y2, x3, y3;

	Triangle(int x1, int y1, int x2, int y2, int x3, int y3) : x1(xToScreen(x1)), y1(yToScreen(y1)), x2(xToScreen(x2)), y2(yToScreen(y2)), x3(xToScreen(x3)), y3(yToScreen(y3)) {};
};