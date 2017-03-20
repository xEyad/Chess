#pragma once
#include <vector>
#include "Vec2.h"
#include "Mouse.h"
#include "Graphics.h"
//there should be no more than ONE object of this class
class Piece;
class Pawn;
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
	std::shared_ptr<Piece> getPiece(Vec2I location, GlobalEnums::pieceType type, GlobalEnums::Team team) const; //original
	std::shared_ptr<Piece> getPiece(int location, GlobalEnums::pieceType type, GlobalEnums::Team team) const //support
	{
		return getPiece(TransLocation(location), type, team);
	}
	std::shared_ptr<Piece> getPiece(Vec2I location) const; //original
	std::shared_ptr<Piece> getPiece(int location) const //support
	{
		return getPiece(TransLocation(location));
	}
	std::shared_ptr<Piece> getPiece(GlobalEnums::pieceType type, GlobalEnums::Team team) const; //original

	int getTurn() const
	{
		return gameTurn;
	}
	bool isGameOver() const
	{
		return gameOver;
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
	bool IsKingsSafe() const
	{
		return !(BkingUnderThreat || WkingUnderThreat);
	}
	bool IsBlackKingSafe() const
	{
		return !BkingUnderThreat;
	}
	bool IsWhiteKingSafe() const
	{
		return !WkingUnderThreat;
	}
	//actions
	void EnterPromotionMode(Piece* p);
	
	//graphical actions
	void SetStage(bool debugMode = false);
	void PawnPromotionScreen(Vec2I mousPos, GlobalEnums::Team team, Color edgesClr, Color highlightClr);
	//logical actions
	void HandleInput(bool cheatMode = false);  //mouse
	std::shared_ptr<Piece> PromoteTo(GlobalEnums::pieceType type);
	bool DoEnPasset(std::shared_ptr<Piece> piece1, std::shared_ptr<Piece> piece2);
	//cheats

	//friend functions
private:
	friend class Board;
	bool DestroyPiece(Piece* piece);
	bool DestroyPiece(std::shared_ptr<Piece> piece);
	//generates moves and checks if king is threatened
	void GenerateMovesForAllPieces();
	void CheckKingsSafety();
private:
	std::vector<std::shared_ptr<Piece>> pieces;
	Board &board;
	Graphics &gfx;
	Mouse &mouse;
	const TextSurface::Font font;

	int board_rows;
	int board_columns;
	int gameTurn = 1; //odd is white's turn
	bool selectionMode = false;
	std::shared_ptr<Piece> selectedPiece = nullptr;
	Color highlight = Colors::Red;	
	bool gameOver = false; //manipulated by board
	Vec2I BKingLoc;
	Vec2I WKingLoc;
	bool WkingUnderThreat = false;
	bool BkingUnderThreat = false;
	std::shared_ptr<Piece> threatningPiece = nullptr;

	Pawn* luckyPawn = nullptr;
	bool promotionMode = false;
	std::vector<RectI> promotionRects;
	Surface* const BpromotionScreen;
	Surface* const WpromotionScreen;
	std::vector<Color> WpromSprSurf;
	std::vector<Color> BpromSprSurf;
};

