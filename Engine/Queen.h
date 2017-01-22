#pragma once
#include "Piece.h"
class Queen :
	public Piece
{
public:
	Queen(Vec2I location, Team team, Board* const board);
	//getters
	virtual int howManyLeft() const; //should return the number of pieces left in this team
	virtual bool isValidLocation(Vec2I newLocation) const ;
	
	//actions
	virtual void moveTo(Vec2I newLocation);
	~Queen();

private:
	//getters
	virtual bool isWayClear(Vec2I newLocation) const; 
	bool isValidRookMove(Vec2I newLocation) const;
	bool isValidBishopMove(Vec2I newLocation) const;
	bool isKingMove(Vec2I newLocation) const;

private:
	static int nWhiteLeft;
	static int nBlackLeft;
};

