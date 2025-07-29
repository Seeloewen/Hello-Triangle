#include "Resolution.h"

float xToScreen(int pix)
{
	return pix / (width / 2.0f) - 1;
}

float yToScreen(int pix)
{
	float f = (height - pix) / (height / 2.0f) - 1;
	return f;
}