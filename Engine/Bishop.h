#pragma once
#include "Piece.h"
class Bishop : public Piece
{
public:
	Bishop(Vec2I location, Team team, Board *const board, Surface* const sprite);
	~Bishop();

	//getters 
	virtual int HowManyLeft() const; 
	virtual bool IsValidLocation(Vec2I newLocation) const;
	virtual bool IsValidLocation(int newLocation) const;
	//actions
	virtual void GenerateValidMoves();

private:
	//getters
	virtual bool IsWayClear(Vec2I newLocation) const;
	virtual bool IsWayClear(int newLocation) const;
private:
	static int nWhiteLeft;
	static int nBlackLeft;
};

