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
	Piece* getPiece(Vec2I location, GlobalEnums::pieceType type, GlobalEnums::Team team) const; //original
	Piece* getPiece(int location, GlobalEnums::pieceType type, GlobalEnums::Team team) const //support
	{
		return getPiece(TransLocation(location), type, team);
	}
	Piece* getPiece(Vec2I location) const; //original
	Piece* getPiece(int location) const //support
	{
		return getPiece(TransLocation(location));
	}
	inline int TransLocation(Vec2I location) const
	{
		return location.y * board_rows + location.x;
	}
	
	inline Vec2I TransLocation(int location) const
	{
		//column = location % totalNumberOfColumns    <= X
		//row = (location - column) / totalNumberOfRows    <= Y
		return{ location % board_columns,(location - (location % board_columns)) / board_rows };
	}
	//actions
	static void addTurn(); //maybe end turn

	//friend functions
	friend class Board;
private:
	std::vector<Piece*> pieces;
	static int gameTurn;
	int board_rows;
	int board_columns;
};

