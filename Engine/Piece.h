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
	struct PreviousTurn
	{
		Vec2I curLocation = this->curLocation;
		Vec2I oldLocation = this->oldLocation;
		bool captured = this->captured;
		bool movedBefore = this->movedBefore;
		int stepsCounter = 0; //only used with pawn
	}; //a variable here
protected:
	Piece(Vec2I location, Team team, pieceType type, Board* const board, Surface* const sprite)
		:
		curLocation(location),
		oldLocation({-1,-1}),
		team(team),
		type(type),
		board(board),
		sprite(sprite)
	{
		if (team == Team::BLACK)
			enemyTeam = Team::WHITE;
		else if (team == Team::WHITE)
			enemyTeam = Team::BLACK;

		ReportChange();

		GenerateValidMoves();

	}
	virtual ~Piece(){}

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
	virtual void ReportChange() //sends to board a pointer to the changed piece
	{
		board->ReadChange(this, oldLocation);
	}

public:
	//getters
	pieceType GetType() const
	{
		return type;
	}
	Team GetTeam() const
	{
		return team;
	}
	Team GetEnemyTeam() const
	{
		return enemyTeam;
	}

	Vec2I Locate() const
	{
		return curLocation;
	}	
	bool isCaptured() const
	{
		return captured;
	}
	 Surface* GetSprite() const
	{
		return sprite;
	}
	const std::vector<Vec2I>& getValidTiles() const
	{
		return validTiles;
	}
	virtual int HowManyLeft() const = 0; //should return the number of pieces left in this team
	virtual bool IsValidLocation(Vec2I newLocation) const = 0; //original
	virtual bool IsValidLocation(int newLocation) const = 0; //support
	bool HasMovedBefore() const
	{
		return movedBefore;
	}
	PreviousTurn LastTurn() const
	{
		return lastTurn;
	}
	//actions
	virtual bool MoveTo(Vec2I newLocation)//original
	{
		if (IsValidLocation(newLocation))
		{
			CopyThisTurn();
			oldLocation = curLocation;
			curLocation = newLocation;
			movedBefore = true;
			ReportChange();
			return true;
		}
		else
			return false;
	}
	virtual bool MoveTo(int newLocation) //support
	{
		return MoveTo(TransLocation(newLocation));
	}
	virtual void UndoMove()
	{
		Vec2I locationGoingTo = curLocation; //this is the location which the piece will leave empty, Board needs to know it
		curLocation = lastTurn.curLocation;
		oldLocation = lastTurn.oldLocation;
		captured = lastTurn.captured;
		movedBefore = lastTurn.movedBefore;
		board->ReadChange(this, locationGoingTo, true); //reporting change with reversed tiles locations
	}
	virtual void CopyThisTurn() 
	{
		lastTurn.curLocation = this->curLocation;
		lastTurn.oldLocation = this->oldLocation;
		lastTurn.captured = this->captured;
		lastTurn.movedBefore = this->movedBefore;
	}
	virtual void GenerateValidMoves() {}; // should be pure virtual
	virtual void SendToPrison()
	{
		captured = true;
		//oldLocation = curLocation;
		//curLocation = Vec2I({ -1,-1 });
	}
	virtual bool PutAt(Vec2I newLocation)
	{
		if (board->IsInsideTheBoard(newLocation))
		{
			CopyThisTurn();
			oldLocation = curLocation;
			curLocation = newLocation;
			ReportChange();
			return true;
		}
		else
			return false;
	}
	virtual bool PutAt(int newLocation)
	{
		return PutAt(TransLocation(newLocation));
	}
	//use for special cases only

	virtual void AddValidTile(Vec2I tileLocation)
	{
		validTiles.push_back(tileLocation);
	}
	//used after destroying a piece (or marking it)
	virtual void ClearValideTiles()
	{
		
		
		validTiles.clear();
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
	std::vector<Vec2I> validTiles;
	bool captured = false; // the piece itself
	bool movedBefore = false;
	PreviousTurn lastTurn;
	//std::vector< CapturedPiece> capturedPieces; //enemy pieces captured by this piece
	Board* const board;
	Surface* const sprite;
};
