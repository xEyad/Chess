#pragma once
#include "Vec2.h"
#include "Colors.h"
#include "GameDirector.h"
#include "Board.h"
#include <iostream>
#include <Windows.h>
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
		if (team == Team::BLACK)
			enemyTeam = Team::WHITE;
		else if (team == Team::WHITE)
			enemyTeam = Team::BLACK;

		try
		{
			reportChange();
		}
		catch ( std::logic_error &e)
		{
			//std::exit(2);
			//auto msg = "Caught a runtime_error exception: " + e;
			e.what(); //just to avoid warnings
			OutputDebugStringA("Caught a runtime_error exception: no more thane 1 piece can be initialized on same spot/Location"); //should find a better way to use this
			//curLocation = oldLocation; //make it disappear from the world!

		}
		
	}
	virtual ~Piece(){}

	//getters
	virtual bool isWayClear(Vec2I newLocation) const = 0; //it checks if the way to the new location (not the newLocation itself) contains other pieces or not
	virtual bool isWayClear(int newLocation) const = 0;//support
	inline int TransLocation(Vec2I location) const
	{
		return location.y * board->rows + location.x;
	}
	inline Vec2I TransLocation(int location) const
	{
		//column = location % totalNumberOfColumns    <= X
		//row = (location - column) / totalNumberOfRows    <= Y
		return{ location % board->columns,(location - (location % board->columns)) / board->rows };
	}
	//actions
	virtual void reportChange() //sends to board a pointer to the changed piece
	{
		board->ReadChange(this, oldLocation);
	}

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
	virtual bool isValidLocation(Vec2I newLocation) const = 0; //original
	virtual bool isValidLocation(int newLocation) const = 0; //support
	//actions
	virtual void moveTo(Vec2I newLocation) = 0;//original
	virtual void moveTo(int newLocation) = 0;//support
	virtual void sendToPrison()
	{
		captured = true;
		oldLocation = curLocation;
		curLocation = Vec2I({ -1,-1 });
	}
	/*struct CapturedPiece
	{
		pieceType type;
		Vec2I vLocation;
		int iLocation;
	};*/
protected:
	const pieceType type = NOT_DEFINED;
	Vec2I curLocation;
	Vec2I oldLocation;
	const Team team;
	Team enemyTeam;
	bool captured = false; // the piece itself
	//std::vector< CapturedPiece> capturedPieces; //enemy pieces captured by this piece
	//std::vector<int> sredPieces; //enemy pieces captured by this piece
	Board* const board;
};

