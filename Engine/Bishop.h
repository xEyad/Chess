#pragma once
#include "Piece.h"
#include "BishopLeg.h"
class Bishop : public Piece
{
public:
	Bishop(Vec2I location, Team team, Board *const board);
	~Bishop();

	//getters 
	virtual int HowManyLeft() const; 
	virtual bool IsValidLocation(Vec2I newLocation) const;
	virtual bool IsValidLocation(int newLocation) const;
	//actions
	virtual void GenerateValidMoves();

private:
	static int nWhiteLeft;
	static int nBlackLeft;
};

