#pragma once
#include "Piece.h"
#include "KingLeg.h"
class King :public Piece
{
public:
	King(Vec2I location, Team team, Board* const board);
	~King();
	//getters
	virtual int HowManyLeft() const; //should return the number of pieces left in this team
	virtual bool IsValidLocation(Vec2I newLocation) const ;
	virtual bool IsValidLocation(int newLocation) const;
	bool HasMovedBefore() const
	{
		return movedBefore;
	}
	//actions
	virtual void GenerateValidMoves();
	virtual bool PutAt(Vec2I newLocation)
	{
		if (board->IsInsideTheBoard(newLocation))
		{
			movedBefore = true;
			return Piece::PutAt(newLocation);
		}
		else
			return false;
	}
	virtual bool PutAt(int newLocation)
	{
		return PutAt(TransLocation(newLocation));
	}

private:
	static int nWhiteLeft;
	static int nBlackLeft;
};

