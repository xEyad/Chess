#pragma once
#include "Rect.h"
#include "Vec2.h"
class Button
{
public:
	Button(unsigned int width, unsigned int height, std::wstring text = L"")
		:
		width(width),
		height(height),
		text(text)
	{}

	Button(Vec2I topLeft, Vec2I botRight, std::wstring text = L"")
		:
		width(abs(topLeft.x-botRight.x)),
		height(abs(topLeft.y - botRight.y)),
		text(text)
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
	Button btn;
	Vec2I topLeftOffset;
};