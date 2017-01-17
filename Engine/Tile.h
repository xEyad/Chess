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
		bool containPiece = false;
		pieceType piecetype = pieceType::NOTDEFINED;
		Team team = Team::INVALID;
	};
private:
	Tile(Vec2I location, Color c)
		:
		color(c),
		location(location)
	{}
	void applyChanges(bool containPiece, pieceType piecetype, Team team)
	{
		state.containPiece = containPiece;
		state.piecetype = piecetype;
		state.team = team;
	}
public:
	const Color color;
	const Vec2I location;

private:
	friend class Board;
	Status state;
};