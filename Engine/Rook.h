#pragma once
#include "Piece.h"
class Rook : public Piece
{
public:
	Rook(Vec2I location, Team team, Board* const board);
	virtual ~Rook();
	
	//getters
	virtual int HowManyLeft() const;
	virtual bool IsValidLocation(int newLocation) const;
	virtual bool IsValidLocation(Vec2I newLocation) const;
	//actions
	virtual bool MoveTo(int newLocation);
	virtual bool MoveTo(Vec2I newLocation);
private:
	//getters
	virtual bool IsWayClear(int newLocation) const;	
	virtual bool IsWayClear(Vec2I newLocation) const;

private:
	bool movedBefore = false;
	static int nWhiteLeft;
	static int nBlackLeft;
};

