#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(Vec2I location, Team team, Board* const board);
	virtual ~Rook();
	
	//getters
	virtual int howManyLeft() const;
	virtual bool isValidLocation(int newLocation) const;
	virtual bool isValidLocation(Vec2I newLocation) const;
	//actions
	virtual void moveTo(int newLocation);
	virtual void moveTo(Vec2I newLocation);
private:
	//getters
	virtual bool isWayClear(int newLocation) const;	
	virtual bool isWayClear(Vec2I newLocation) const;

private:
	bool movedBefore = false;
	static int nWhiteLeft;
	static int nBlackLeft;
};

