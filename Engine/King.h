#pragma once
#include "Piece.h"
class King :
	public Piece
{
public:
	King(Vec2I location, Team team, Board* const board);
	~King();
	//getters
	virtual int howManyLeft() const; //should return the number of pieces left in this team
	virtual bool isValidLocation(Vec2I newLocation) const ;
	//actions
	virtual void moveTo(Vec2I newLocation);

private:
	//getters
	virtual bool isWayClear(Vec2I newLocation) const;//will be used only in the special case

private:
	bool movedBefore = false;
	static int nWhiteLeft;
	static int nBlackLeft;
};

