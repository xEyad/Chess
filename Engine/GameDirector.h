#pragma once
#include <vector>
#include <algorithm>
#include "Vec2.h"
#include "Mouse.h"
#include "Graphics.h"

//there should be no more than ONE object of this class
class Piece;
class Pawn;
class Board;
class Tile;
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
	struct DEFENDOR
	{
		std::shared_ptr<Pawn> pawn;
		int turnRegistered;
		Vec2I locationOfDefense;
	};
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
	bool AreKingsSafe() const
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
	bool IsTileUnderThreatBy(Vec2I TileLocation,GlobalEnums::Team ThreatningTeam);
	bool AreTilesUnderThreat(std::vector<Vec2I> Tileslocations, GlobalEnums::Team ThreatningTeam);
	//actions
	void EnterPromotionMode(Piece* p);
	void RerollTurn(std::shared_ptr<Piece> piece);
	//graphical actions
	void SetStage(bool debugMode = false);
	void PawnPromotionScreen(Vec2I mousPos, GlobalEnums::Team team, Color edgesClr, Color highlightClr);
	//logical actions
	void HandleInput(bool cheatMode = false);  //mouse
	void PromoteTo(GlobalEnums::pieceType type);
	bool DoCastling(std::shared_ptr<Piece> piece1, std::shared_ptr<Piece> piece2);
	bool DoEnPassant(std::shared_ptr<Piece> piece, std::shared_ptr<Tile> tile);
	void CheckForEnPassants();
	//cheats

	//friend functions
private:
	friend class Board;
	void MarkForDestruction(std::shared_ptr<Piece> pieceToDestroy);
	void RemoveDestructionMark();
	void DestroyMarkedPiece();
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
	std::shared_ptr<Piece> pieceToDestroy = nullptr;
	Pawn* luckyPawn = nullptr;
	bool promotionMode = false;
	std::vector<RectI> promotionRects;
	Surface* const BpromotionScreen;
	Surface* const WpromotionScreen;
	std::vector<Color> WpromSprSurf;
	std::vector<Color> BpromSprSurf;
	std::vector <std::shared_ptr<Pawn>>	whiteOffensors; //white pawns on 4th row  
	std::vector <std::shared_ptr<Pawn>>	blackOffensors; //black pawns on 5th row  
	std::vector <DEFENDOR>				whiteDefendors; //white pawns on 5th row  
	std::vector <DEFENDOR>				blackDefendors; //black pawns on 4th row 
};

