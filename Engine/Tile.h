#pragma once
#include "Colors.h"
#include "Vec2.h"
#include "GameDirector.h" // for Global enums
using namespace GlobalEnums;
class Tile
{
private:
	struct Status
	{
		bool containPiece;
		pieceType piecetype;
		Team team;
	};
private:
	Tile(Vec2I location, Color c)
		:
		color(c),
		location(location)
	{}
	
public:
	const Color color;
	const Vec2I location;

private:
	friend class Board;
	Status state;
};