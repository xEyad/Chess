#pragma once
#include "Vec2.h"
#include "Colors.h"
//abstract class 
class Piece
{
public:
	enum pieceType
	{
		PAWN,
		KNIGHT,
		ROOK,
		BISHOP,
		QUEEN,
		KING,
		NOTDEFINED
	};
protected:
	virtual pieceType type() const = 0;
	virtual Vec2I locate() const = 0;
	virtual void moveTo(Vec2I location) = 0;
protected:
	pieceType type = NOTDEFINED;
	Vec2I location;
	Color team;

};

