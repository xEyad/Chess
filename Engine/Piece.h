#pragma once
#include "Vec2.h"
#include "Colors.h"
#include "Board.h"
#include "GameDirector.h" // for the enums
using namespace GlobalEnums;
//abstract class 
class Piece
{
protected:
	Piece(Vec2I location, Team team, pieceType type, const Board* const board)
		:
		location(location),
		team(team),
		type(type),
		board(board)
	{}
	virtual ~Piece(){}

public:
	//getters
	virtual pieceType getType() const
	{
		return type;
	}
	virtual Vec2I locate() const
	{
		return location;
	}
	virtual int howManyLeft() const = 0; //should return the number of pieces left in this team
	virtual bool isValidLocation(Vec2I newLocation) const = 0;
	//actions
	virtual void moveTo(Vec2I newLocation) = 0;

protected:
	const pieceType type = NOTDEFINED;
	Vec2I location;
	const Team team;
	const Board* const board;
};