#pragma once
#include "Piece.h"
#include "RookLeg.h"
class Rook : public Piece
{
public:
	Rook(Vec2I location, Team team, Board* const board, Surface* const sprite);
	virtual ~Rook();
	
	//getters
	virtual int HowManyLeft() const;
	virtual bool IsValidLocation(int newLocation) const;
	virtual bool IsValidLocation(Vec2I newLocation) const;
	
	//actions
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
	static int nWhiteLeft;
	static int nBlackLeft;
};

