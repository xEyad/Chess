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
	virtual bool isValidLocation(int newLocation) const;
	//actions
	virtual void moveTo(Vec2I newLocation);
	virtual void moveTo(int newLocation);

private:
	//getters
	virtual bool isWayClear(Vec2I newLocation) const;
	virtual bool isWayClear(int newLocation) const;
private:
	static int nWhiteLeft;
	static int nBlackLeft;
};

