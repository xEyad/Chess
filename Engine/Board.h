#pragma once
#include "Tile.h"
#include <memory>
class Board
{
public:
	Board(int rows, int columns);
	std::shared_ptr<Tile> getTile(Vec2I location) const;
	const Tile::Status getTileState(Vec2I location) const;
public:
	const int rows; 
	const int columns;
	std::vector<std::shared_ptr<Tile>> boardTiles; //array of shared pointers of type Tile 
};

