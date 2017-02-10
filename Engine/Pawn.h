#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(Vec2I location,Team team,  Board * const board);
	virtual ~Pawn();

	//getters
	virtual int HowManyLeft() const;
	virtual bool IsValidLocation(int newLocation) const;
	virtual bool IsValidLocation(Vec2I newLocation) const;
	//actions
	virtual void MoveTo(int newLocation);
	virtual void MoveTo(Vec2I newLocation);

private:
	//getters
	virtual bool IsWayClear(Vec2I newLocation) const;//will be used only in the special case
	virtual bool IsWayClear(int newLocation) const;
private:
	bool movedBefore = false;
	static int nWhiteLeft;
	static int nBlackLeft;
	friend class pawnTest;
};

