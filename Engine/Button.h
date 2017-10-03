#pragma once
#include "Rect.h"
#include "Vec2.h"
class Button
{
public:
	Button(unsigned int width, unsigned int height, std::wstring text)
		:
		width(width),
		height(height),
		text(text)
	{}

	Button(Vec2I topLeft, Vec2I botRight, std::wstring text)
		:
		width(abs(topLeft.x - botRight.x)),
		height(abs(topLeft.y - botRight.y)),
		text(text)
	{}
	Button(unsigned int width, unsigned int height)
		:
		Button(width,height,L"")
	{}	
	Button(Vec2I topLeft, Vec2I botRight)
		:
		Button(topLeft, botRight, L"")
	{}
	

	RectI GetBoundingBox(Vec2I topLeftPointLocation) const
	{
		return RectI(topLeftPointLocation, { int(topLeftPointLocation.x + width),int(topLeftPointLocation.y + height)});
	}
private:
	unsigned int width;
	unsigned int height;
	std::wstring text;
};

//just a button and its offset from a location (topleft)
struct GuidedButton
{
	GuidedButton(Button btn, Vec2I topLeftOffset)
		:
		btn(btn),
		topLeftOffset(topLeftOffset)
	{}
	RectI GetBoundingBox(Vec2I topLeftPointLocation) const
	{
		return btn.GetBoundingBox(topLeftPointLocation + topLeftOffset);
	}
	Button btn;
	Vec2I topLeftOffset;
};