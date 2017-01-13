#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(Vec2I location,Team team, const Board *board);
	virtual ~Pawn();

	//getters
	virtual int howManyLeft() const;
	virtual bool isValidLocation(Vec2I newLocation) const;

	//actions
	virtual void moveTo(Vec2I newLocation);

private:
	bool movedBefore = false;
	static int nWhiteLeft;
	static int nBlackLeft;
	friend class pawnTest;
};

