#include "BoardPainter.h"



BoardPainter::BoardPainter(Graphics& gfx,const Board &board)
	:
	Painter(gfx),
	board(board),
	sprite(new Surface(Surface::FromFile(L"Resources\\Chess Board\\Stone Grey\\Chess_Board_Stone2_nolabel.png")))
{
}


BoardPainter::~BoardPainter()
{
}

void BoardPainter::DrawSprite()
{
	gfx.DrawSpriteClipped(sprite, { 0,0 });
}

void BoardPainter::DrawGrid(Vec2I TopLeft, Color edgesClr) const
{
	int tileWidth = Board::Tile::WIDTH;
	int tileHeight = Board::Tile::HEIGHT;
	int xx = 0;
	int yy = 0;
	Vec2I screenLocation = TopLeft;
	for (auto i = board.GetAllTiles()->cbegin(); i < board.GetAllTiles()->cend(); i++)
	{
		//each tile location is topLeft corner of any Rect
		Vec2I startPoint(screenLocation.x + xx, screenLocation.y + yy);
		Vec2I endPoint(startPoint.x + tileWidth, startPoint.y + tileHeight);
		gfx.DrawRect(RectI(startPoint, endPoint), edgesClr);
		xx += tileWidth;
		if ((*i)->location.x % (board.rows - 1) == 0 && (*i)->location.x != 0) //first one = 0, if we pass the 7 then its new row
		{
			//go to the beginning and down a little bit
			xx = 0;
			yy += tileHeight;
		}
	}
}

void BoardPainter::HighlightTile(Vec2I GridTopleft,Vec2I mousePos, Color edgesClr) const
{
	auto tile = board.GetTileByMouse(GridTopleft,mousePos);
	if (tile)
	{
		Vec2I startPoint(GridTopleft.x + tile->location.x * Board::Tile::WIDTH, GridTopleft.y + tile->location.y * Board::Tile::HEIGHT);
		Vec2I endPoint(startPoint.x + Board::Tile::WIDTH, startPoint.y + Board::Tile::HEIGHT);
		RectI tileRect(startPoint, endPoint);

		if (tileRect.Contains(mousePos))
			gfx.DrawColoredRect(tileRect, edgesClr, 72, false); //change value to 80+ if you don't want the small square 
	}		
}

void BoardPainter::HighlightTiles(Vec2I GridTopleft,std::vector<Vec2I> tilesPos, Color edgesClr) const
{
	for (auto i = tilesPos.cbegin(); i < tilesPos.cend(); i++)
	{
		auto tile = board.GetTile(*i);
		Vec2I startPoint(GridTopleft.x + tile->location.x * Board::Tile::WIDTH, GridTopleft.y + tile->location.y * Board::Tile::HEIGHT);
		Vec2I endPoint(startPoint.x + Board::Tile::WIDTH, startPoint.y + Board::Tile::HEIGHT);
		Vec2I centerPoint(startPoint.x + (Board::Tile::WIDTH / 2), startPoint.y + (Board::Tile::HEIGHT / 2));
		int size = Board::Tile::WIDTH / 9;
		RectI r(centerPoint.y - size, centerPoint.y + size, centerPoint.x - size, centerPoint.x + size);
		//gfx.DrawColoredRect(RectI(startPoint, endPoint), edgesClr, 72, false); //change value to 80+ if you don't want the small square 
		//gfx.DrawColoredRect(RectI(startPoint, endPoint), edgesClr, -72, true); //change value to 80+ if you don't want the small square 
		gfx.DrawColoredRect(r, edgesClr);
	}
}

void BoardPainter::DrawLabels(Vec2I GridTopleft,Color labelsClr) const
{
	static TextSurface::Font fonto(L"times", 15.0f);

	for (int cols = 0; cols < 8; cols++)
	{
		Vec2I start(GridTopleft.x + 35, GridTopleft.y);
		int offSetX = Board::Tile::WIDTH;
		int offSetY = -21;

		Vec2I topRowLabels(start.x + offSetX*cols, start.y + offSetY);
		Vec2I botRowLabels(topRowLabels.x, start.y - offSetY * 4 - 7 + topRowLabels.y + Board::Tile::HEIGHT * (board.columns - 1));

		gfx.DrawText(std::to_wstring(cols), topRowLabels, fonto, labelsClr);
		gfx.DrawText(std::to_wstring(cols), botRowLabels, fonto, labelsClr);
	}
	for (int rows = 0; rows < 8; rows++)
	{
		Vec2I start(GridTopleft.x, GridTopleft.y + 35);
		int offSetX = -20;
		int offSetY = Board::Tile::HEIGHT;

		Vec2I topRowLabels(start.x + offSetX, start.y + offSetY*rows);
		Vec2I botRowLabels(topRowLabels.x + Board::Tile::WIDTH * (board.rows - 1) - offSetX * 5 + 3, topRowLabels.y);

		gfx.DrawText(std::to_wstring(rows), topRowLabels, fonto, labelsClr);
		gfx.DrawText(std::to_wstring(rows), botRowLabels, fonto, labelsClr);
	}
}
//1-stoneGrey, 2-stoneBlue, 3-stoneBlack, 4-wood
void BoardPainter::ChangeSpriteTo(BoardSprites spritePic)
{
	switch (spritePic)
	{
		case BoardSprites::StoneGrey:
			delete sprite;
			sprite = new Surface(Surface::FromFile(L"Resources\\Chess Board\\Stone Grey\\Chess_Board_Stone2_nolabel.png"));
			break;
		case BoardSprites::StoneBlue:
			delete sprite;
			sprite = new Surface(Surface::FromFile(L"Resources\\Chess Board\\Stone Blue\\Chess_Board_Stone3_nolabel.png"));
			break;
		case BoardSprites::StoneBlack:
			delete sprite;
			sprite = new Surface(Surface::FromFile(L"Resources\\Chess Board\\Stone Black\\Chess_Board_Stone_nolabel.png"));
			break;
		default: //case 4 Wood
			delete sprite;
			sprite = new Surface(Surface::FromFile(L"Resources\\Chess Board\\Wood\\Chess_Board_wood_nolabel.png"));
			break;
		
	}
}
