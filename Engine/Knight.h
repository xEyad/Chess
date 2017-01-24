#pragma once
#include "Piece.h"
class Knight :
	public Piece
{
public:
	Knight(Vec2I location, Team team, Board* const board);
	~Knight();
	//getters
	virtual int howManyLeft() const; //should return the number of pieces left in this team
	virtual bool isValidLocation(Vec2I newLocation) const;

	//actions
	virtual void moveTo(Vec2I newLocation);

private:
	//getters
	virtual bool isWayClear(Vec2I newLocation) const; //isn't used
private:
	static int nWhiteLeft;
	static int nBlackLeft;
	
};

