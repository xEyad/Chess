#pragma once
//there should be no more than ONE object of this class
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
	GameDirector();
	static void addTurn();

public:
	static int gameTurn;
};

