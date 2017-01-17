#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(Vec2I location, Team team, Board *const board);
	~Bishop();

	//getters 
	virtual int howManyLeft() const; 
	virtual bool isValidLocation(Vec2I newLocation) const;
	virtual bool isWayClear(Vec2I newLocation) const;
	//actions
	virtual void moveTo(Vec2I newLocation);

private:
	static int nWhiteLeft;
	static int nBlackLeft;
};

