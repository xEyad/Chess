#pragma once
#include <vector>
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
		NOTDEFINED
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
	static void addTurn();
public:
	std::vector<Piece*> pieces;
	static int gameTurn;
};

