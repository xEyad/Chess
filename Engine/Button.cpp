#include "Button.h"

Button::Button(unsigned int width, unsigned int height, std::wstring text, Color txt, Color edges, Color fill, bool haveEdges,bool haveFill)
	:
	width(width),
	height(height),
	text(text),
	txtClr(txt),
	edgesClr(edges),
	edges(haveEdges),
	fill(haveFill)
{}

Button::Button(Vec2I topLeft, Vec2I botRight, std::wstring text, Color txt, Color edges, Color fill, bool haveEdges, bool haveFill)
	:
	width(abs(topLeft.x - botRight.x)),
	height(abs(topLeft.y - botRight.y)),
	text(text),
	txtClr(txt),
	edgesClr(edges),
	edges(haveEdges),
	fill(haveFill)
{}

Button Button::CreateNormalButton(unsigned int width, unsigned int height, std::wstring text)
{
	return Button(width, height, text, Colors::White, Colors::White,Colors::White,true,false);
}

Button Button::CreateColorfulButton(unsigned int width, unsigned int height, std::wstring text, Color edges, Color textClr)
{
	return Button(width, height, text, textClr, edges, Colors::White, true, false);
}

Button Button::CreateTextlessButton(unsigned int width, unsigned int height)
{
	return Button(width, height, L"", Colors::White, Colors::White, Colors::White, true, false);
}

Button Button::CreateEdgelessButton(unsigned int width, unsigned int height, std::wstring text)
{
	return Button(width, height, text, Colors::White, Colors::White, Colors::White, false, false);
}

Button Button::CreateFilledButton(unsigned int width, unsigned int height, std::wstring text,Color fillClr)
{
	return Button(width, height, text, Colors::White, Colors::White, fillClr, false, true);
}

RectI Button::GetBoundingBox(Vec2I topLeftPointLocation) const
{
	return RectI(topLeftPointLocation, { int(topLeftPointLocation.x + width),int(topLeftPointLocation.y + height) });
}

std::wstring Button::Text() const
{
	return text;
}

Color Button::TextColor() const
{
	return txtClr;
}

Color Button::EdgesColor() const
{
	return edgesClr;
}

Color Button::FillColor() const
{
	return fillClr;
}

bool Button::HaveFill() const
{
	return fill;
}

bool Button::HaveEdges() const
{
	return edges;
}
