#pragma once
#include "Piece.h"
class Knight :
	public Piece
{
public:
	Knight(Vec2I location, Team team, Board* const board);
	~Knight();
	//getters
	virtual int HowManyLeft() const; //should return the number of pieces left in this team
	virtual bool IsValidLocation(int newLocation) const;
	virtual bool IsValidLocation(Vec2I newLocation) const;

	//actions
	virtual bool MoveTo(int newLocation);
	virtual bool MoveTo(Vec2I newLocation);

private:
	//getters
	virtual bool IsWayClear(Vec2I newLocation) const; //isn't used
	virtual bool IsWayClear(int newLocation) const;
private:
	static int nWhiteLeft;
	static int nBlackLeft;
	
};

