#pragma once
#include "Tile.h"
#include <memory>
class Board
{
public:
	Board(int rows, int columns);
public:
	const int rows; 
	const int columns;
	std::vector<std::unique_ptr<Tile>> boardTiles; //array of Unique pointers of type Tile
};

