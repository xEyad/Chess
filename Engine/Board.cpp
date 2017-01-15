#include "Board.h"
#include "Tile.h"

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

