#pragma once
#include "Tile.h"
#include <memory>
class Piece;
class Board
{
public:
	Board(int rows, int columns);
	//getters
	std::shared_ptr<Tile> getTile(Vec2I location) const;
	const Tile::Status getTileState(Vec2I location) const;	
	bool isInsideTheBoard(Vec2I location) const;

	//actions
	void ReadChange(Piece* piece,Vec2I oldLocation);
public:
	const int rows; 
	const int columns;
	std::vector<std::shared_ptr<Tile>> boardTiles; //array of shared pointers of type Tile 
};

