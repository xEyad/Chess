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
	virtual bool isValidLocation(int newLocation) const;
	virtual bool isValidLocation(Vec2I newLocation) const;

	//actions
	virtual void moveTo(int newLocation);
	virtual void moveTo(Vec2I newLocation);

private:
	//getters
	virtual bool isWayClear(Vec2I newLocation) const; //isn't used
	virtual bool isWayClear(int newLocation) const;
private:
	static int nWhiteLeft;
	static int nBlackLeft;
	
};

