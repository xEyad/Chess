#pragma once
#include "Piece.h"
class Queen :
	public Piece
{
public:
	Queen(Vec2I location, Team team, Board* const board, Surface* const sprite);
	~Queen();

	//getters
	virtual int HowManyLeft() const; //should return the number of pieces left in this team
	virtual bool IsValidLocation(int newLocation) const;
	virtual bool IsValidLocation(Vec2I newLocation) const ;
	
	//actions
	virtual bool MoveTo(int newLocation);
	virtual bool MoveTo(Vec2I newLocation);
	virtual void GenerateValidMoves();

private:
	//getters
	virtual bool IsWayClear(Vec2I newLocation) const; 
	virtual bool IsWayClear(int newLocation) const;
	bool isValidRookMove(Vec2I newLocation) const;
	bool isValidBishopMove(Vec2I newLocation) const;
	bool isKingMove(Vec2I newLocation) const;

private:
	static int nWhiteLeft;
	static int nBlackLeft;
};

