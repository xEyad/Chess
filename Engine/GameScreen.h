#pragma once
#include "Vec2.h"
#include "Graphics.h"
#include "Button.h"

//interface for any screen in the game
class GameScreen
{
public:
	GameScreen();
	GameScreen(int width,int height);
	virtual ~GameScreen() = 0;

	int Width() const;
	int Height() const;
	RectI Rect() const;

	const std::vector<GuidedSurface> GuidedSprites() const;	
	const std::vector<Text> Messages() const;
	const std::vector<GuidedButton> MappedButtons() const;

protected:
	void setWidth(int w);
	void setHeight(int h);
protected:
	int width;
	int height;
	RectI screenRect;

	//new variables
	std::vector<GuidedSurface> sprites;
	std::vector<Text> messages;
	std::vector<GuidedButton> buttons;
};

