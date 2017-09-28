#include "GameScreen.h"



GameScreen::GameScreen(int width, int height)
	:
	width(width),
	height(height)
{
}

GameScreen::~GameScreen()
{
}

int GameScreen::Width() const
{
	return width;
}

int GameScreen::Height() const
{
	return height;
}


RectI GameScreen::Rect() const
{
	return screenRect;
}

const  std::vector<GuidedSurface> GameScreen::GuidedSprites() const
{
	return sprites;
}

//const std::vector< TextSurface::Font> GameScreen::Fonts() const
//{
//	return fonts;
//}

const std::vector<GuidedButton> GameScreen::MappedButtons() const
{
	return buttons;
}

