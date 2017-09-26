#include "BoardPainter.h"



BoardPainter::BoardPainter(Graphics& gfx)
	:
	Painter(gfx),
	sprite(new Surface(Surface::FromFile(L"Resources\\Chess Board\\Stone Grey\\Chess_Board_Stone2_nolabel.png")))
{
}


BoardPainter::~BoardPainter()
{
}

void BoardPainter::DrawSprite()
{
	for (unsigned int x = 0; x < sprite->GetWidth(); x++)
	{
		for (unsigned int y = 0; y < sprite->GetHeight(); y++)
		{
			gfx.PutPixel(x, y, sprite->GetPixel(x, y));
		}
	}
}

void BoardPainter::DrawSprite(int spriteNum)
{
	ChangeSpriteTo(spriteNum);
	DrawSprite();
}

void BoardPainter::DrawGrid(const Board &board, Vec2I TopLeft, Color edgesClr) const
{
	int tileWidth = Board::GetTileWidth();
	int tileHeight = Board::GetTileHeight();
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

//1-stoneGrey, 2-stoneBlue, 3-stoneBlack, 4-wood
void BoardPainter::ChangeSpriteTo(int spriteNum)
{
	switch (spriteNum)
	{
		case 1:
			delete sprite;
			sprite = new Surface(Surface::FromFile(L"Resources\\Chess Board\\Stone Grey\\Chess_Board_Stone2_nolabel.png"));
			break;
		case 2:
			delete sprite;
			sprite = new Surface(Surface::FromFile(L"Resources\\Chess Board\\Stone Blue\\Chess_Board_Stone3_nolabel.png"));
			break;
		case 3:
			delete sprite;
			sprite = new Surface(Surface::FromFile(L"Resources\\Chess Board\\Stone Black\\Chess_Board_Stone_nolabel.png"));
			break;
		default: //case 4
			delete sprite;
			sprite = new Surface(Surface::FromFile(L"Resources\\Chess Board\\Wood\\Chess_Board_wood_nolabel.png"));
			break;
		
	}
}
