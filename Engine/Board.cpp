#include "Board.h"
#include "Piece.h"
#include <iostream>
#include "GameDirector.h"

const int Tile::HEIGHT = 90;
const int Tile::WIDTH = 90;
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

std::shared_ptr<Tile> Board::GetTile(Vec2I location) const
{
	for each (std::shared_ptr<Tile> t in boardTiles)
	{
		if (t->location == location)
			return t;
	}
	return nullptr;
}
std::shared_ptr<Tile> Board::GetTileByMouse(Vec2I mousePos) const
{
	//check if its inside any tile
	int xx = 0;
	int yy = 0;
	Vec2I screenLocation = topLeft;
	for (auto i = boardTiles.cbegin(); i < boardTiles.cend(); i++)
	{
		//each tile location is topLeft corner of any Rect
		Vec2I startPoint(screenLocation.x + xx, screenLocation.y + yy);
		Vec2I endPoint(startPoint.x + Tile::WIDTH, startPoint.y + Tile::HEIGHT);
		xx += Tile::WIDTH;

		//if mouse is inside this rectangle (tile)
		if (mousePos.x > startPoint.x && mousePos.x < endPoint.x && mousePos.y > startPoint.y && mousePos.y < endPoint.y)
			return *i;

		if ((*i)->location.x % (8 - 1) == 0 && (*i)->location.x != 0) //first one = 0, if we pass the 7 then its new row
		{
			//go to the beginning and down a little bit
			xx = 0;
			yy += Tile::HEIGHT;
		}
	}
	return nullptr;
}
const Tile::Status Board::GetTileState(Vec2I location) const
{
	if (IsInsideTheBoard(location))
		return GetTile(location)->state;
	else
	{
		Tile::Status s;
		s.containPiece = false;
		s.piecetype = pieceType::NOT_DEFINED;
		s.pieceTeam = Team::INVALID;
		return s;
	}
}

bool Board::IsInsideTheBoard(Vec2I location) const
{
	if (location.y < rows && location.x < columns && location.y >= 0 && location.x >= 0)		
		return true;
	else
		return false;
}

void Board::ReadChange(Piece * piece, Vec2I oldLocation)
{//board checks the piece for new changes and adapt itself to it

	//intialization case (can't add two pieces in the same location)
	if (!IsInsideTheBoard(oldLocation))
	{
		auto Tile = GetTile(piece->Locate());
		if (Tile->state.containPiece)
		{
			throw  std::logic_error("no more than 1 piece can be initialized on same spot/Location"); //handled in piece constructor
			return;
		}			
	}
	//do changes to the tile which the piece moved from
	else if (IsInsideTheBoard(oldLocation)) //basically not intialization
	{
		auto prevTile = GetTile(oldLocation);
		prevTile->applyChanges(false, pieceType::NOT_DEFINED, Team::INVALID); //supposing that we left this tile empty
	}
	//do changes to the tile which the piece moved to
	auto tile = GetTile(piece->Locate());
	if (tile->state.containPiece)
	{
		//if this has moved then the new tile is either empty or have enemy piece.
		//if it contains a piece then we send it to prison.
		director->getPiece(piece->Locate(),tile->state.piecetype,tile->state.pieceTeam)->SendToPrison();
	}
	
	tile->applyChanges(true, piece->GetType(), piece->GetTeam());
}

void Board::Draw( Graphics & gfx, Color edgesClr, Vec2I TopLeft)
{
	int xx = 0;
	int yy = 0;
	topLeft = TopLeft;
	Vec2I screenLocation = topLeft;
	for (auto i = boardTiles.cbegin(); i < boardTiles.cend(); i++)
	{
		//each tile location is topLeft corner of any Rect
		Vec2I startPoint(screenLocation.x + xx,screenLocation.y + yy);
		Vec2I endPoint(startPoint.x + Tile::WIDTH, startPoint.y + Tile::HEIGHT);
		gfx.DrawRect(RectI(startPoint, endPoint), edgesClr);
		xx += Tile::WIDTH;
		if ((*i)->location.x % (rows-1) == 0 && (*i)->location.x != 0) //first one = 0, if we pass the 7 then its new row
		{
			//go to the beginning and down a little bit
			xx = 0;
			yy += Tile::HEIGHT;
		}
	}
}

void Board::Draw(Graphics & gfx, Color edgesClr) const
{
	int xx = 0;
	int yy = 0;
	Vec2I screenLocation = topLeft;
	for (auto i = boardTiles.cbegin(); i < boardTiles.cend(); i++)
	{
		//each tile location is topLeft corner of any Rect
		Vec2I startPoint(screenLocation.x + xx, screenLocation.y + yy);
		Vec2I endPoint(startPoint.x + Tile::WIDTH, startPoint.y + Tile::HEIGHT);
		gfx.DrawRect(RectI(startPoint, endPoint), edgesClr);
		xx += Tile::WIDTH;
		if ((*i)->location.x % (rows - 1) == 0 && (*i)->location.x != 0) //first one = 0, if we pass the 7 then its new row
		{
			//go to the beginning and down a little bit
			xx = 0;
			yy += Tile::HEIGHT;
		}
	}
}

void Board::HighlightTile(Graphics & gfx, Vec2I mousePos, Color edgesClr) const
{
	//check if its inside any tile
	int xx = 0;
	int yy = 0;
	Vec2I screenLocation = topLeft;
	for (auto i = boardTiles.cbegin(); i < boardTiles.cend(); i++)
	{
		//each tile location is topLeft corner of any Rect
		Vec2I startPoint(screenLocation.x + xx, screenLocation.y + yy);
		Vec2I endPoint(startPoint.x + Tile::WIDTH, startPoint.y + Tile::HEIGHT);
		xx += Tile::WIDTH;

		//if mouse is inside this rectangle (tile)
		if (mousePos.x > startPoint.x && mousePos.x < endPoint.x && mousePos.y > startPoint.y && mousePos.y < endPoint.y)
			gfx.DrawRect(RectI(startPoint, endPoint), edgesClr);

		if ((*i)->location.x % (8 - 1) == 0 && (*i)->location.x != 0) //first one = 0, if we pass the 7 then its new row
		{
			//go to the beginning and down a little bit
			xx = 0;
			yy += Tile::HEIGHT;
		}
	}
}

void Board::DrawPieces( Graphics & gfx) const
{
	Color c;
	Vec2I screenLocation = topLeft;
	for (auto i = director->pieces.cbegin(); i < director->pieces.cend(); i++)
	{
		if (IsInsideTheBoard((*i)->Locate()))
		{
			//give it a color based on its type
			switch ((*i)->GetType())
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
			Vec2I centerPoint(screenLocation.x + (*i)->Locate().x * Tile::WIDTH + 45, screenLocation.y + (*i)->Locate().y * Tile::HEIGHT + 45);
			int size = Tile::WIDTH / 4;
			RectI r(centerPoint.y - size, centerPoint.y + size, centerPoint.x - size, centerPoint.x + size);
			gfx.DrawColoredRect(r, c);
		}
		else
			continue;
	}
}

