#include "GameScreen.h"



GameScreen::GameScreen(int width, int height, Graphics & gfx)
	:
	width(width),
	height(height),
	gfx(gfx),
	currentTopLeft({-1,-1})
{
}

GameScreen::~GameScreen()
{
}

void GameScreen::Draw(Vec2I topLeft)
{
	currentTopLeft = topLeft;
	screenRect = RectI(topLeft, { topLeft.x + width, topLeft.y + height });
}

int GameScreen::Width() const
{
	return width;
}

int GameScreen::Height() const
{
	return height;
}

Vec2I GameScreen::CurrentTopLeft() const
{
	return currentTopLeft;
}

RectI GameScreen::Rect() const
{
	return screenRect;
}

