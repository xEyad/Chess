#pragma once
#include "Vec2.h"
#include "Colors.h"
#include "GameDirector.h"
#include "Board.h"
#include <iostream>
using namespace GlobalEnums;
//abstract class
class Piece
{
protected:
	Piece(Vec2I location, Team team, pieceType type, Board* const board)
		:
		curLocation(location),
		oldLocation({-1,-1}),
		team(team),
		type(type),
		board(board)
	{
		try
		{
			reportChange();
		}
		catch (std::logic_error &e)
		{
			//std::exit(2);
			std::cerr << "Caught a runtime_error exception: " << e.what() << '\n';
			curLocation = oldLocation; //make it disappear from the world!

		}
		
	}
	virtual ~Piece(){}

public:
	//getters
	virtual pieceType getType() const
	{
		return type;
	}
	virtual Team getTeam() const
	{
		return team;
	}
	virtual Vec2I locate() const
	{
		return curLocation;
	}		
	virtual int howManyLeft() const = 0; //should return the number of pieces left in this team
	virtual bool isValidLocation(Vec2I newLocation) const = 0;
	virtual bool isWayClear(Vec2I newLocation) const = 0; //it checks if the way to the new location (not the newLocation itself) contains other pieces or not
	//actions
	virtual void moveTo(Vec2I newLocation) = 0;
	virtual void reportChange() //sends to board a pointer to the changed piece
	{
		board->ReadChange(this,oldLocation);
	}
protected:
	const pieceType type = NOTDEFINED;
	Vec2I curLocation;
	Vec2I oldLocation;
	const Team team;
	Board* const board;
};