#pragma once
#include "Piece.h"
class Knight :	public Piece
{
public:
	Knight(Vec2I location, Team team, Board* const board, Surface* const sprite);
	~Knight();
	//getters
	virtual int HowManyLeft() const; //should return the number of pieces left in this team
	virtual bool IsValidLocation(int newLocation) const;
	virtual bool IsValidLocation(Vec2I newLocation) const;

	//actions
	virtual void GenerateValidMoves();

private:
	static int nWhiteLeft;
	static int nBlackLeft;
	
};

