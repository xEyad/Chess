#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>
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
	constexpr char * pieceTypeStrings[] = { "PAWN","KNIGHT","ROOK","BISHOP","QUEEN","KING","NOT_DEFINED" };
	enum class Team
	{
		WHITE,
		BLACK,
		INVALID
	};
	constexpr char * teamStrings[] = {"WHITE","BLACK","INVALID"};
}

class GameDirector
{	
public:
	GameDirector(Board &board, Graphics &gfx,Mouse &mouse);
	GameDirector(Board &board, Graphics &gfx, Mouse &mouse, std::string saveFile);
	//should be in global enums
	char * GetTextForpieceType(int enumVal)
	{
		return GlobalEnums::pieceTypeStrings[enumVal];
	}
	char * GetTextForTeam(int enumVal)
	{
		return GlobalEnums::teamStrings[enumVal];
	}
	GlobalEnums::Team GetTeamFromText(std::string team)
	{
		if (team == "BLACK" || team == "black")
		{
			return GlobalEnums::Team::BLACK;
		}
		else if (team == "WHITE" || team == "white")
		{
			return GlobalEnums::Team::WHITE;
		}
		else
			return GlobalEnums::Team::INVALID;
	}
	GlobalEnums::pieceType GetPieceTypeFromText(std::string type)
	{
		if (type == "PAWN" || type == "pawn")		
			return GlobalEnums::pieceType::PAWN;
		else if (type == "ROOK" || type == "rook")		
			return GlobalEnums::pieceType::ROOK;
		else if (type == "BISHOP" || type == "bishop")
			return GlobalEnums::pieceType::BISHOP;
		else if (type == "KING" || type == "king")		
			return GlobalEnums::pieceType::KING;
		else if (type == "KNIGHT" || type == "knight")		
			return GlobalEnums::pieceType::KNIGHT;
		else if (type == "QUEEN" || type == "queen")		
			return GlobalEnums::pieceType::QUEEN;
		else
			return GlobalEnums::pieceType::NOT_DEFINED;
	}
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
	void SaveGame(std::string saveFile);
	void QuickSaveGame();
	void LoadGame(std::string saveFile);
	void QuickLoadGame();
	//graphical actions
	void SetStage(bool debugMode = false);
	void DrawStartMenu(Vec2I mousPos);
	void DrawPawnPromotionScreen(Vec2I mousPos, GlobalEnums::Team team, Color edgesClr, Color highlightClr);
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

	//buttons
	class Button
	{
	public:
		Button(Vec2I location, unsigned int width, unsigned int height, std::wstring text)
			:
			location(location),
			width(width),
			height(height),
			text(text),
			botRight({ location.x + int(width) ,location.y + int(height) }),
			boundingBox(location,botRight)
		{}
		RectI GetBoundingBox() const
		{
			return boundingBox;
		}
		void Draw(Graphics &gfx, const TextSurface::Font &font, unsigned int offsetX = 0, unsigned int offsetY = 0, Color backgroundClr = Colors::Black, Color textClr = Colors::White)
		{
			for ( int x = location.x; x < botRight.x ; x++)
			{
				for ( int y = location.y; y < botRight.y ; y++)
				{
					gfx.PutPixel(x, y, backgroundClr);
				}
			}
			if(offsetX > width)
				offsetX = 0;
			if (offsetY > height)
				offsetY = 0;

			gfx.DrawText(L"Start", Vec2I(location.x + offsetX, location.y + offsetY ), font, textClr);
		}

		
	private:
		Vec2I location;
		Vec2I botRight;
		unsigned int width;
		unsigned int height;
		std::wstring text;
		const RectI boundingBox;
	};
};

