#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Vec2.h"
#include "Mouse.h"
#include "MouseInputHandler.h"
#include "Graphics.h"
#include "BlackPromotionScreen.h"
#include "WhitePromotionScreen.h"
//there should be no more than ONE object of this class
//GameDirector responsibility is to check for the pieces special conditions and game rules ONLY
class Piece;
class Pawn;
class Board;
class GiveMeTile;
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
	}  //M
	char * GetTextForTeam(int enumVal)
	{
		return GlobalEnums::teamStrings[enumVal];
	}  //M
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
	}  //M
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
	}  //M
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
	const  std::vector<std::shared_ptr<Piece>>* getPieces() const;
	

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
	//actions , M = should be moved
	void EnterPromotionMode(Piece* p); //M the section where it draws
	void RerollTurn(std::shared_ptr<Piece> piece);	//M
	void SaveGame(std::string saveFile);//M
	void QuickSaveGame();//M
	void LoadGame(std::string saveFile);//M
	void QuickLoadGame(); //M
	//graphical actions
	void SetStage(bool debugMode = false); //M
	void DrawStartMenu(Vec2I mousPos); //M
	void DrawPawnPromotionScreen(Vec2I mousPos, GlobalEnums::Team team, Color edgesClr, Color highlightClr); //M
	void DrawWhoseTurn(Color clr); //M
	void DrawTurn(Color clr); //M
	void DrawThreatWarning(Color clr); //M
	//logical actions
	void HandleInput(bool cheatMode = false);  //mouse ,  //M
	void PromoteTo(GlobalEnums::pieceType type);
	bool DoCastling(std::shared_ptr<Piece> piece1, std::shared_ptr<Piece> piece2);
	bool DoEnPassant(std::shared_ptr<Piece> piece, Vec2I tileLoc);
	void CheckForEnPassants();
	//cheats
	
	
	//friend functions
private:
	friend Board;
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
	Graphics &gfx; //M
	Mouse &mouse; //M
	const TextSurface::Font font; //M

	int board_rows;
	int board_columns;
	int gameTurn = 1; //odd is white's turn
	bool selectionMode = false; //M
	std::shared_ptr<Piece> selectedPiece = nullptr; //M
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
	std::vector<RectI> promotionRects; //M
	//buttons //M
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

