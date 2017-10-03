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
#include "ScreenPainter.h"
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
	class DirectorEvent
	{
	public:
		enum Type
		{
			EnterWhitePromotion,
			EnterBlackPromotion,
			KingUnderThreat,
			KingIsSafe,
			GameOver,
			TurnPassed, //for increasing gameTurns
			Invalid
		};
	private:
		Type type;
	public:
		DirectorEvent()
			:
			type(Invalid)
		{}
		DirectorEvent(Type type)
			:
			type(type)
		{}
		bool IsValid() const
		{
			return type != Invalid;
		}
		Type GetType() const
		{
			return type;
		}
	};
public:
	GameDirector(Board &board);
	GameDirector(Board &board, std::string saveFile);
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
	DirectorEvent ReadEvent();
	bool IsThereEvents() const;
	bool isGameOver() const
	{
		return gameOver;
	}
	int TransLocation(Vec2I location) const
	{
		return location.y * board_rows + location.x;
	}	
	Vec2I TransLocation(int location) const
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
	bool WillKingBeDead(std::shared_ptr<Piece> movingPiece) const;
	bool IsTileUnderThreatBy(Vec2I TileLocation,GlobalEnums::Team ThreatningTeam);
	bool AreTilesUnderThreat(std::vector<Vec2I> Tileslocations, GlobalEnums::Team ThreatningTeam);
	//actions , M = should be moved
	void EnterPromotionMode(Piece* p); 
	void RerollTurn(std::shared_ptr<Piece> piece);	//M
	void SaveGame(std::string saveFile);//M
	void QuickSaveGame();//M
	void LoadGame(std::string saveFile);//M
	void QuickLoadGame(); //M
	//graphical actions
	void DrawStartMenu(Vec2I mousPos); //M

	//logical actions
	void HandleInput(const Vec2I tile1Location, const Vec2I tile2Location, GlobalEnums::Team teamToPlay, int gameTurn);
	void HandleInputCheatMode(const Vec2I tile1Location, const Vec2I tile2Location, int gameTurn);
	void PromoteTo(GlobalEnums::pieceType type);
	bool DoCastling(std::shared_ptr<Piece> piece1, std::shared_ptr<Piece> piece2);
	bool DoEnPassant(std::shared_ptr<Piece> piece, Vec2I tileLoc);
	void CheckForEnPassants(int gameTurn);
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
	void CheckKingsSafety(); //here it adds event kingThreat
private:
	std::vector<std::shared_ptr<Piece>> pieces;
	Board &board;

	int board_rows;
	int board_columns;
	
	Color highlight = Colors::Red;	
	bool gameOver = false; //manipulated by board
	Vec2I BKingLoc;
	Vec2I WKingLoc;
	bool WkingUnderThreat = false;
	bool BkingUnderThreat = false;
	std::shared_ptr<Piece> threatningPiece = nullptr;
	std::shared_ptr<Piece> pieceToDestroy = nullptr;
	Pawn* luckyPawn = nullptr;
	
	std::queue<DirectorEvent> gameEvents; //should be filled here, and emptied in gameManager with the respective action executed!
};

