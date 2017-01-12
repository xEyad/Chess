#pragma once
#include "Tile.h"
#include <memory>
class Board
{
public:
	Board(int rows, int columns);
public:
	int rows; //size of chess board = 64 square total 8*8
	int columns;
	std::vector<std::unique_ptr<Tile>> boardTiles; //array of Unique pointers of type Tile
};

