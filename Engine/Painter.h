#pragma once
#include "Graphics.h"
//this class know how to draw anything , and the sole responsible for drawing . no other class should be able to use GFX directly!
class Painter
{
public:
	Painter(Graphics &gfx);
	virtual ~Painter() = 0;

protected:
	Graphics &gfx;
};

