#pragma once
#include <vector>
#include <algorithm>
#include <iostream>
#include <fstream>
#include <cstdio>
#include "Vec2.h"
#include "Mouse.h"
#include "GlobalEnums.h"
#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"

//GameDirector responsibility is to check if the game rules are being followed by keeping an eye on pieces and the board
class GameDirector
{	
public:
	enum class DirectorEvent
	{
		EnterWhitePromotion,
		EnterBlackPromotion,
		KingUnderThreat,
		KingIsSafe,
		GameOver,
		TurnPassed, //for increasing gameTurns
		Invalid
	};
public:
	GameDirector(Board &board);
	
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
		return location.y * board.rows + location.x;
	}	
	Vec2I TransLocation(int location) const
	{
		//column = location % totalNumberOfColumns    <= X
		//row = (location - column) / totalNumberOfRows    <= Y
		return{ location % board.columns,(location - (location % board.columns)) / board.rows };
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
	//actions
	void EnterPromotionMode(Piece* p); 
	void RerollTurn(std::shared_ptr<Piece> piece);	
	void ChangeGamePieces(std::vector<std::shared_ptr<Piece>> newPieces);	

	//logical actions
	bool MovePiece(std::shared_ptr<Piece> piece, Vec2I Location);
	bool PutPieceAt(std::shared_ptr<Piece> piece, Vec2I Location); //doesn't give a fuck about game rules
	void HandleInput(const Vec2I tile1Location, const Vec2I tile2Location,const GlobalEnums::Team teamToPlay,const int gameTurn);
	void HandleInputCheatMode(const Vec2I tile1Location,const Vec2I tile2Location,const GlobalEnums::Team teamToPlay,const int gameTurn); 
	void PromoteTo(GlobalEnums::pieceType type);
	bool DoCastling(std::shared_ptr<Piece> piece1, std::shared_ptr<Piece> piece2);
	bool DoEnPassant(std::shared_ptr<Piece> piece, Vec2I tileLoc);
	void CheckForEnPassants(int gameTurn);

	
	
private:
	void MarkForDestruction(std::shared_ptr<Piece> pieceToDestroy);
	void RemoveDestructionMark();
	void DestroyMarkedPiece();
	bool DestroyPiece(Piece* piece);
	bool DestroyPiece(std::shared_ptr<Piece> piece);
	//generates moves and checks if king is threatened
	void GenerateMovesForAllPieces();
	void CheckKingsSafety(); //here it adds event kingThreat
	void ReflectChangesToBoard(std::shared_ptr<Piece> piece); //called after the piece had actually done a move
private:
	std::vector<std::shared_ptr<Piece>> pieces;
	Board &board;

	bool gameOver = false; 
	Vec2I BKingLoc;
	Vec2I WKingLoc;
	bool WkingUnderThreat = false;
	bool BkingUnderThreat = false;
	std::shared_ptr<Piece> threatningPiece = nullptr;
	std::shared_ptr<Piece> pieceToDestroy = nullptr;
	Pawn* luckyPawn = nullptr;
	
	std::queue<DirectorEvent> gameEvents; //should be filled here, and emptied in gameManager with the respective action executed!
};

