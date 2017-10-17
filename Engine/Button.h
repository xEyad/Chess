#pragma once
#include "Rect.h"
#include "Vec2.h"
#include "Colors.h"
class Button
{
public:
	Button(unsigned int width, unsigned int height, std::wstring text, Color txt, Color edges, Color fill, bool haveEdges, bool haveFill);
		

	Button(Vec2I topLeft, Vec2I botRight, std::wstring text, Color txt, Color edges, Color fill, bool haveEdges, bool haveFill);
	
	// fast constructors
	static Button CreateNormalButton(unsigned int width, unsigned int height, std::wstring text);
	static Button CreateColorfulButton(unsigned int width, unsigned int height, std::wstring text,Color edges,Color textClr);
	static Button CreateTextlessButton(unsigned int width, unsigned int height);
	static Button CreateEdgelessButton(unsigned int width, unsigned int height, std::wstring text);
	static Button CreateFilledButton(unsigned int width, unsigned int height, std::wstring text, Color fillClr);
	
	//getters
	RectI GetBoundingBox(Vec2I topLeftPointLocation) const;	
	std::wstring Text() const;	
	Color TextColor() const;	
	Color EdgesColor() const;
	Color FillColor() const;
	bool HaveFill() const;
	bool HaveEdges() const;
private:
	unsigned int width;
	unsigned int height;  
	std::wstring text; 
	Color txtClr;
	bool edges;
	Color edgesClr;
	Color fillClr;
	bool fill;
};

//just a button and its offset from a location (topleft)
struct GuidedButton
{
	GuidedButton(Button btn, Vec2I topLeftOffset, bool haveHighlight ,Color highlight, std::string name,bool highlightText = false)
		:
		btn(btn),
		topLeftOffset(topLeftOffset),
		haveHighlight(haveHighlight),
		highlight(highlight),
		highlightText(highlightText),
		name(name)
	{}
	RectI GetBoundingBox(Vec2I topLeftPointLocation) const
	{
		return btn.GetBoundingBox(topLeftPointLocation + topLeftOffset);
	}
	Button btn;
	Vec2I topLeftOffset;
	Color highlight;
	bool haveHighlight;
	bool highlightText;
	std::string name;
};