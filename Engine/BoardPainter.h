#pragma once
#include "Painter.h"
#include "Board.h"
class Tile;
class BoardPainter : public Painter
{
public:
	BoardPainter(Graphics& gfx, const Board &board);
	~BoardPainter();

	//1-stoneGrey, 2-stoneBlue, 3-stoneBlack, 4-wood
	void DrawSprite(int spriteNum);
	void DrawGrid(Vec2I TopLeft, Color edgesClr = Colors::White) const;
	void HighlightTile(Vec2I GridTopleft, Vec2I mousePos, Color edgesClr) const;
	void HighlightTiles(Vec2I GridTopleft,std::vector<Vec2I> tilesPos, Color edgesClr) const;
	void DrawLabels(Vec2I GridTopleft,Color labelsClr) const;
private:
	//1-stoneGrey, 2-stoneBlue, 3-stoneBlack, 4-wood
	void ChangeSpriteTo(int spriteNum);
private:
	Surface*  sprite;
	const Board &board;
};

