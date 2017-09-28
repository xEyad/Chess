#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Button.h"

//interface for any screen in the game
class GameScreen
{
public:
	GameScreen(int width,int height);
	virtual ~GameScreen() = 0;

	int Width() const;
	int Height() const;
	RectI Rect() const;

	const std::vector<GuidedSurface> GuidedSprites() const;
	
	//const std::vector<TextSurface::Font> Fonts() const;
	const std::vector<GuidedButton> MappedButtons() const;
protected:
	int width;
	int height;
	RectI screenRect;

	//new variables
	std::vector<GuidedSurface> sprites;
	std::vector<TextSurface::Font> fonts;
	std::vector<GuidedButton> buttons;
};

