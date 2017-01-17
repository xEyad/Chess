#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(Vec2I location, Team team, Board* const board);
	virtual ~Rook();
	
	//getters
	virtual int howManyLeft() const;
	virtual bool isValidLocation(Vec2I newLocation) const;
	virtual bool isWayClear(Vec2I newLocation) const;
	//actions
	virtual void moveTo(Vec2I newLocation);

private:
	bool movedBefore = false;
	static int nWhiteLeft;
	static int nBlackLeft;
};

