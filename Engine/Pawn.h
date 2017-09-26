#pragma once
#include "Piece.h"
class Pawn : public Piece
{
public:
	Pawn(Vec2I location, Team team, Board * const board,int nStepsMoved = 0);
	virtual ~Pawn();

	//getters
	virtual int HowManyLeft() const;
	virtual int nStepsMoved() const
	{
		return stepsCounter;
	}
	virtual bool IsValidLocation(int newLocation) const;
	virtual bool IsValidLocation(Vec2I newLocation) const;
	bool isTransformed() const
	{
		return transformed;
	}
	//actions
	virtual bool MoveTo(Vec2I newLocation) override;
	virtual void UndoMove() override;
	virtual void GenerateValidMoves();
private:
	//getters
	virtual bool IsWayClear(Vec2I newLocation) const;//will be used only in the special case
	virtual bool IsWayClear(int newLocation) const;
	//actions
	virtual void CopyThisTurn() override;
private:
	int stepsCounter = 0;
	bool transformed = false;
	static int nWhiteLeft;
	static int nBlackLeft;
};

