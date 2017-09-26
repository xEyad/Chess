#pragma once
#include "Piece.h"
#include "QueenLeg.h"
class Queen :
	public Piece
{
public:
	Queen(Vec2I location, Team team, Board* const board);
	~Queen();

	//getters
	virtual int HowManyLeft() const; //should return the number of pieces left in this team
	virtual bool IsValidLocation(int newLocation) const;
	virtual bool IsValidLocation(Vec2I newLocation) const ;
	
	//actions
	virtual void GenerateValidMoves();


private:
	static int nWhiteLeft;
	static int nBlackLeft;
};

