#pragma once
#include "Painter.h"
#include "Board.h"
class Tile;
class BoardPainter : public Painter
{
public:
	enum class BoardSprites
	{
		StoneGrey,
		StoneBlue,
		StoneBlack,
		Wood
	};
public:
	BoardPainter(Graphics& gfx, const Board &board);
	~BoardPainter();

	void DrawSprite();
	void DrawGrid(Vec2I TopLeft, Color edgesClr = Colors::White) const;
	void HighlightTile(Vec2I GridTopleft, Vec2I mousePos, Color edgesClr) const;
	void HighlightTiles(Vec2I GridTopleft,std::vector<Vec2I> tilesPos, Color edgesClr) const;
	void DrawLabels(Vec2I GridTopleft,Color labelsClr) const;
	void ChangeSpriteTo(BoardSprites spritePic);
private:
	Surface*  sprite;
	const Board &board;
};

