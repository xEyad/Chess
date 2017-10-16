#pragma once
#include "Painter.h"
#include "GameScreen.h"
class ScreenPainter :	public Painter
{
public:
	ScreenPainter(Graphics& gfx);
	~ScreenPainter();

	void DrawScreenWithHighlights(GameScreen& screen, Vec2I topLeft,Vec2I mousePos);
	void DrawScreen( GameScreen& screen, Vec2I topLeft);
private:
	void DrawSprites(const GameScreen& screen, Vec2I topLeft); //if ther is
	void DrawTexts(const GameScreen& screen, Vec2I topLeft); //if there is 
	void DrawButtons(const GameScreen& screen, Vec2I topLeft); //if there is 
	void DoHighlights(const GameScreen& screen, Vec2I topLeft, Vec2I mousePos); //if there is 
};

