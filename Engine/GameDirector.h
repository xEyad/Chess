#pragma once
#include <vector>
#include "Vec2.h"
//there should be no more than ONE object of this class
class Piece;
class Board;
namespace GlobalEnums
{
	enum pieceType
	{
		PAWN,
		KNIGHT,
		ROOK,
		BISHOP,
		QUEEN,
		KING,
		NOT_DEFINED
	};
	enum class Team
	{
		WHITE,
		BLACK,
		INVALID
	};
}


class GameDirector
{
public:
	GameDirector(Board &board);
	//getters

	//select piece
	Piece* getPiece(Vec2I location, GlobalEnums::pieceType type, GlobalEnums::Team team) const;
	Piece* getPiece(Vec2I location) const;
	//actions
	static void addTurn();

	//friend functions
	friend class Board;
private:
	std::vector<Piece*> pieces;
	static int gameTurn;
};

