#pragma once
#include <vector>
#include "Vec2.h"
#include "Mouse.h"
#include "Graphics.h"
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
	GameDirector(Board &board, Graphics &gfx,Mouse &mouse);
	//getters
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
	int getTurn() const
	{
		return gameTurn;
	}
	GlobalEnums::Team WhoseTurn() const
	{
		if (gameTurn % 2 == 0) //even
			return GlobalEnums::Team::BLACK;
		else //odd
			return GlobalEnums::Team::WHITE;
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

	//graphical actions
	void SetStage();
	//logical actions
	void HandleInput();  //mouse


	//cheats

	//free moving and clicking using mouse (no turns)
	void CH_HandleInput();  
	//friend functions
	friend class Board;
private:
	std::vector<Piece*> pieces;
	Board &board;
	Graphics &gfx;
	Mouse &mouse;
	int board_rows;
	int board_columns;
	int gameTurn = 1; //odd is white
	bool selectionMode = false;
	Color highlight = Colors::Red;	
};

