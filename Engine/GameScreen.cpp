#include "GameScreen.h"



GameScreen::GameScreen()
{
}

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

const std::vector<Text> GameScreen::Messages() const
{
	return messages;
}

const std::vector<GuidedButton> GameScreen::MappedButtons() const
{
	return buttons;
}

void GameScreen::setWidth(int w)
{
	width = w;
}

void GameScreen::setHeight(int h)
{
	height = h;
}

