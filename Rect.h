#pragma once

#include "Resolution.h"

struct Rect
{
	float x1, y1, x2, y2;

	Rect(int x1, int y1, int x2, int y2) : x1(xToScreen(x1)), y1(yToScreen(y1)), x2(xToScreen(x2)), y2(yToScreen(y2)) {};
};