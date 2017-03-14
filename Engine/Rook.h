#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(Vec2I location, Team team, Board* const board, Surface* const sprite);
	virtual ~Rook();
	
	//getters
	virtual int HowManyLeft() const;
	virtual bool IsValidLocation(int newLocation) const;
	virtual bool IsValidLocation(Vec2I newLocation) const;
	bool HasMovedBefore() const
	{
		return movedBefore;
	}
	//actions
	virtual bool MoveTo(int newLocation);
	virtual bool MoveTo(Vec2I newLocation);
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
	virtual void GenerateValidMoves();
private:
	//getters
	virtual bool IsWayClear(int newLocation) const;	
	virtual bool IsWayClear(Vec2I newLocation) const;

private:
	bool movedBefore = false;
	static int nWhiteLeft;
	static int nBlackLeft;
};

