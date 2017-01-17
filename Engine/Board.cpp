#include "Board.h"
#include "Tile.h"
#include "Piece.h"
#include <iostream>
Board::Board(int rows, int columns)
	:
	rows(rows),
	columns(columns)
{
	//i should give tiles names (a2,b5) ... but thats for later

	//Color c[] = { Colors::Black, Colors::White };
	Color c[] = { Colors::Blue, Colors::White };
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
	return getTile(location)->state;
}
bool Board::isInsideTheBoard(Vec2I location) const
{
	if (location.y <= rows && location.x <= columns && location.y >= 0 && location.x >= 0)		
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
			throw  std::logic_error("no more thane 1 piece can be initialized on same spot/Location"); //handled in piece constructor
			return;
		}			
	}
	//do changes to the tile that piece moved from
	else if (isInsideTheBoard(oldLocation)) //basically not intialization
	{
		auto prevTile = getTile(oldLocation);
		prevTile->applyChanges(false, pieceType::NOTDEFINED, Team::INVALID); //supposing that we left this tile empty
	}
	//do changes to the tile that piece moved to
	auto tile = getTile(piece->locate());
	tile->applyChanges(true, piece->getType(), piece->getTeam());
}

