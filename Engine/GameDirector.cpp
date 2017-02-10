#include "GameDirector.h"
#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
GameDirector::GameDirector(Board &board)
{
	board_rows = board.rows;
	board_columns = board.columns;

	//spawn the pieces
	int boardWidth = board.rows;
	for (int row = 0; row < board.rows; row++)
	{
		for (int col = 0; col < board.columns; col++)
		{
			int location = row * boardWidth + col; //for easier manipulation			
												   //Rows are Y , Columns are X
			if (location >= 8 && location <= 15)
				pieces.push_back(new Pawn(Vec2I{ col,row }, Team::BLACK, &board));
			else if (location >= 48 && location <= 55)
				pieces.push_back(new Pawn(Vec2I{ col,row }, Team::WHITE, &board));
			else
			{
				switch (location)
				{
					case 0:
						pieces.push_back(new Rook(Vec2I{ col,row }, Team::BLACK, &board));
						break;
					case 1:
						pieces.push_back(new Knight(Vec2I{ col,row }, Team::BLACK, &board));
						break;
					case 2:
						pieces.push_back(new Bishop(Vec2I{ col,row }, Team::BLACK, &board));
						break;
					case 3:
						pieces.push_back(new Queen(Vec2I{ col,row }, Team::BLACK, &board));
						break;
					case 4:
						pieces.push_back(new King(Vec2I{ col,row }, Team::BLACK, &board));
						break;
					case 5:
						pieces.push_back(new Bishop(Vec2I{ col,row }, Team::BLACK, &board));
						break;
					case 6:
						pieces.push_back(new Knight(Vec2I{ col,row }, Team::BLACK, &board));
						break;
					case 7:
						pieces.push_back(new Rook(Vec2I{ col,row }, Team::BLACK, &board));
						break;
					case 63 - 0:
						pieces.push_back(new Rook(Vec2I{ col,row }, Team::WHITE, &board));
						break;
					case 63 - 1:
						pieces.push_back(new Knight(Vec2I{ col,row }, Team::WHITE, &board));
						break;
					case 63 - 2:
						pieces.push_back(new Bishop(Vec2I{ col,row }, Team::WHITE, &board));
						break;
					case 63 - 3:
						pieces.push_back(new Queen(Vec2I{ col,row }, Team::WHITE, &board));
						break;
					case 63 - 4:
						pieces.push_back(new King(Vec2I{ col,row }, Team::WHITE, &board));
						break;
					case 63 - 5:
						pieces.push_back(new Bishop(Vec2I{ col,row }, Team::WHITE, &board));
						break;
					case 63 - 6:
						pieces.push_back(new Knight(Vec2I{ col,row }, Team::WHITE, &board));
						break;
					case 63 - 7:
						pieces.push_back(new Rook(Vec2I{ col,row }, Team::WHITE, &board));
						break;
					default:
						break;
				}
			}
		}
	}
}

Piece* GameDirector::getPiece(Vec2I location, GlobalEnums::pieceType type, GlobalEnums::Team team) const
{
	for each (Piece* p in pieces)
	{
		if (p->GetType() == type && p->GetTeam() == team && p->Locate() == location)
			return p;
	}
	return nullptr;
}

Piece* GameDirector::getPiece(Vec2I location) const
{
	for each (Piece* p in pieces)
	{
		if (p->Locate() == location)
			return p;
	}
	return nullptr;
}

void GameDirector::addTurn()
{
	gameTurn++;
}

int GameDirector::gameTurn = 1;