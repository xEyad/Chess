#pragma once
#include "Piece.h"
class King :
	public Piece
{
public:
	King(Vec2I location, Team team, Board* const board);
	~King();
	//getters
	virtual int HowManyLeft() const; //should return the number of pieces left in this team
	virtual bool IsValidLocation(Vec2I newLocation) const ;
	virtual bool IsValidLocation(int newLocation) const;
	//actions
	virtual void MoveTo(Vec2I newLocation);
	virtual void MoveTo(int newLocation);
private:
	//getters
	virtual bool IsWayClear(Vec2I newLocation) const;//will be used only in the special case
	virtual bool IsWayClear(int newLocation) const;
private:
	bool movedBefore = false;
	static int nWhiteLeft;
	static int nBlackLeft;
};

