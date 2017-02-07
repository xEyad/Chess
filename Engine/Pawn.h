#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(Vec2I location,Team team,  Board * const board);
	virtual ~Pawn();

	//getters
	virtual int howManyLeft() const;
	virtual bool isValidLocation(int newLocation) const;
	virtual bool isValidLocation(Vec2I newLocation) const;
	//actions
	virtual void moveTo(int newLocation);
	virtual void moveTo(Vec2I newLocation);

private:
	//getters
	virtual bool isWayClear(Vec2I newLocation) const;//will be used only in the special case
	virtual bool isWayClear(int newLocation) const;
private:
	bool movedBefore = false;
	static int nWhiteLeft;
	static int nBlackLeft;
	friend class pawnTest;
};

