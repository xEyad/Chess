#pragma once
#include "Painter.h"
#include "Board.h"
class Tile;
class BoardPainter : public Painter
{
public:
	BoardPainter(Graphics& gfx);
	~BoardPainter();

	void DrawSprite();
	//1-stoneGrey, 2-stoneBlue, 3-stoneBlack, 4-wood
	void DrawSprite(int spriteNum);
	void DrawGrid(const Board &board, Vec2I TopLeft, Color edgesClr = Colors::White) const;
private:
	//1-stoneGrey, 2-stoneBlue, 3-stoneBlack, 4-wood
	void ChangeSpriteTo(int spriteNum);
private:
	Surface*  sprite;
};

