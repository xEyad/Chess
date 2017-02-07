#include "Board.h"
#include "Piece.h"
#include <iostream>
#include "GameDirector.h"
Board::Board(int rows, int columns)
	:
	rows(rows),
	columns(columns),
	director(nullptr)
{
	//i should give tiles names (a2,b5) ... but thats for later

	Color c[] = { Colors::Black, Colors::White };
	int i = 1; //first tile is white
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++)
		{
			//Rows are Y , Columns are X
			boardTiles.push_back( std::shared_ptr<Tile> (new Tile(Vec2I(col,row),c[i])));
			i++;
			if (i > 1) //so that i goes 0-1 to alternate between white and black
				i = 0;
		}
		i++;
		if (i > 1) //so that i goes 0-1 to alternate between white and black
			i = 0;
	}
}

std::shared_ptr<Tile> Board::getTile(Vec2I location) const
{
	for each (std::shared_ptr<Tile> t in boardTiles)
	{
		if (t->location == location)
			return t;
	}
	return nullptr;
}

const Tile::Status Board::getTileState(Vec2I location) const
{
	if (isInsideTheBoard(location))
		return getTile(location)->state;
	else
	{
		Tile::Status s;
		s.containPiece = false;
		s.piecetype = pieceType::NOT_DEFINED;
		s.pieceTeam = Team::INVALID;
		return s;
	}
}

bool Board::isInsideTheBoard(Vec2I location) const
{
	if (location.y < rows && location.x < columns && location.y >= 0 && location.x >= 0)		
		return true;
	else
		return false;
}

void Board::ReadChange(Piece * piece, Vec2I oldLocation)
{//board checks the piece for new changes and adapt itself to it

	//intialization case (can't add two pieces in the same location)
	if (!isInsideTheBoard(oldLocation))
	{
		auto Tile = getTile(piece->locate());
		if (Tile->state.containPiece)
		{
			throw  std::logic_error("no more than 1 piece can be initialized on same spot/Location"); //handled in piece constructor
			return;
		}			
	}
	//do changes to the tile which the piece moved from
	else if (isInsideTheBoard(oldLocation)) //basically not intialization
	{
		auto prevTile = getTile(oldLocation);
		prevTile->applyChanges(false, pieceType::NOT_DEFINED, Team::INVALID); //supposing that we left this tile empty
	}
	//do changes to the tile which the piece moved to
	auto tile = getTile(piece->locate());
	if (tile->state.containPiece)
	{
		//if this has moved then the new tile is either empty or have enemy piece.
		//if it contains a piece then we send it to prison.
		director->getPiece(piece->locate(),tile->state.piecetype,tile->state.pieceTeam)->sendToPrison();
	}
	
	tile->applyChanges(true, piece->getType(), piece->getTeam());
}

void Board::Draw( Graphics & gfx,Vec2I topLeft, Color edgesClr, int widthOfTile, int heightOfTile) const
{
	int xx = 0;
	int yy = 0;
	Vec2I screenLocation = topLeft;
	for (auto i = boardTiles.cbegin(); i < boardTiles.cend(); i++)
	{
		//each tile location is topLeft corner of any Rect
		Vec2I startPoint(screenLocation.x + xx,screenLocation.y + yy);
		Vec2I endPoint(startPoint.x + widthOfTile, startPoint.y + heightOfTile);
		gfx.DrawRect(RectI(startPoint, endPoint), edgesClr);
		xx += widthOfTile;
		if ((*i)->location.x % (rows-1) == 0 && (*i)->location.x != 0) //first one = 0, if we pass the 7 then its new row
		{
			//go to the beginning and down a little bit
			xx = 0;
			yy += heightOfTile;
		}
	}
}

void Board::highlightTile(Graphics & gfx, Vec2I mousePos, Color edgesClr, int widthOfTile, int heightOfTile) const
{
	//check if its inside any tile
	int xx = 0;
	int yy = 0;
	Vec2I screenLocation = { 40,40 };
	for (auto i = boardTiles.cbegin(); i < boardTiles.cend(); i++)
	{
		//each tile location is topLeft corner of any Rect
		Vec2I startPoint(screenLocation.x + xx, screenLocation.y + yy);
		Vec2I endPoint(startPoint.x + 90, startPoint.y + 90);
		xx += 90;

		if (mousePos.x > startPoint.x && mousePos.x < endPoint.x && mousePos.y > startPoint.y && mousePos.y < endPoint.y)
			gfx.DrawRect(RectI(startPoint, endPoint), Colors::Red);

		if ((*i)->location.x % (8 - 1) == 0 && (*i)->location.x != 0) //first one = 0, if we pass the 7 then its new row
		{
			//go to the beginning and down a little bit
			xx = 0;
			yy += 90;
		}
	}
}
void Board::DrawPieces( Graphics & gfx,  Vec2I topLeft, int widthOfTile, int heightOfTile ) const
{
	Color c;
	Vec2I screenLocation = topLeft;
	for (auto i = director->pieces.cbegin(); i < director->pieces.cend(); i++)
	{
		if (isInsideTheBoard((*i)->locate()))
		{
			//give it a color based on its type
			switch ((*i)->getType())
			{
				case QUEEN:
					c = Colors::Red;
					break;
				case KING:
					c = Colors::Magenta;
					break;
				case BISHOP:
					c = Colors::Cyan;
					break;
				case ROOK:
					c = Colors::Yellow;
					break;
				case PAWN:
					c = Colors::Green;
					break;
				case KNIGHT:
					c = Colors::LightGray;
					break;
				default:
					c = Colors::Black;
					break;
			}
			Vec2I centerPoint(screenLocation.x + (*i)->locate().x * widthOfTile + 45, screenLocation.y + (*i)->locate().y * heightOfTile + 45);
			int size = widthOfTile / 4;
			RectI r(centerPoint.y - size, centerPoint.y + size, centerPoint.x - size, centerPoint.x + size);
			gfx.DrawColoredRect(r, c);
		}
		else
			continue;
	}
}