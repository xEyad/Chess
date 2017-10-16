#pragma once
#include "Graphics.h"
//this class is the sole responsible for drawing anything , no other class should use GFX directly!
class Painter
{
public:
	Painter(Graphics &gfx);
	virtual ~Painter() = 0;

protected:
	Graphics &gfx;
};

