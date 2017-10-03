#pragma once
#include "Painter.h"
#include "GameScreen.h"
class ScreenPainter :	public Painter
{
public:
	ScreenPainter(Graphics& gfx);
	~ScreenPainter();

	void DrawScreen( GameScreen& screen, Vec2I topLeft);
	void SetButtonsEdgeClr(Color clr);
private:
	void DrawSprites(const GameScreen& screen, Vec2I topLeft); //if ther is
	void DrawTexts(const GameScreen& screen); //if there is 
	void DrawButtons(const GameScreen& screen, Vec2I topLeft); //if there is 
private:
	Color btnsEdgeClr;
};

