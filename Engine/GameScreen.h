#pragma once
#include "Vec2.h"
#include "Graphics.h"

//interface for any screen in the game
class GameScreen
{
public:
	GameScreen(int width,int height, Graphics& gfx);
	virtual ~GameScreen();

	virtual void Draw(Vec2I topLeft) = 0;

	int Width() const;
	int Height() const;
	Vec2I CurrentTopLeft() const;
	RectI Rect() const;
protected:
	int width;
	int height;
	Graphics& gfx;
	Vec2I currentTopLeft;
	RectI screenRect;
};

