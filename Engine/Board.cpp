#include "Board.h"


Board::Board(int rows, int columns)
	:
	rows(rows),
	columns(columns)
{
	//i should give tiles names (a2,b5) ... but thats for later

	//Color c[] = { Colors::Black, Colors::White };
	Color c[] = { Colors::Red, Colors::Green };
	int i = 1; //first tile is white
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++)
		{
			boardTiles.push_back( std::unique_ptr<Tile> (new Tile(Vec2I(row,col),c[i])));
			i++;
			if (i > 1) //so that i goes 0-1 to alternate between white and black
				i = 0;
		}
	}
}

