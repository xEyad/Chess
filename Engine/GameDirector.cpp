#include "GameDirector.h"
#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"

#define WPawnSprite  L"Resources\\Chess Pieces\\Wood\\PawnW.bmp"
#define BPawnSprite  L"Resources\\Chess Pieces\\Wood\\PawnB.bmp"
#define WRookSprite  L"Resources\\Chess Pieces\\Wood\\RookW.bmp"
#define BRookSprite  L"Resources\\Chess Pieces\\Wood\\RookB.bmp"
#define WKnightSprite  L"Resources\\Chess Pieces\\Wood\\KnightW.bmp"
#define BKnightSprite  L"Resources\\Chess Pieces\\Wood\\KnightB.bmp"
#define WBishopSprite  L"Resources\\Chess Pieces\\Wood\\BishopW.bmp"
#define BBishopSprite  L"Resources\\Chess Pieces\\Wood\\BishopB.bmp"
#define WQueenSprite  L"Resources\\Chess Pieces\\Wood\\QueenW.bmp"
#define BQueenSprite  L"Resources\\Chess Pieces\\Wood\\QueenB.bmp"
#define WKingSprite  L"Resources\\Chess Pieces\\Wood\\KingW.bmp"
#define BKingSprite  L"Resources\\Chess Pieces\\Wood\\KingB.bmp"

GameDirector::GameDirector(Board &board,Graphics &gfx, Mouse &mouse)
	:
	board(board),
	gfx(gfx),
	mouse(mouse)
{
	//Rows are Y , Columns are X
	board_rows = board.rows;
	board_columns = board.columns;
	//spawn the pieces
	int boardWidth = board.rows;
	for (int row = 0; row < board.rows; row++)
	{
		for (int col = 0; col < board.columns; col++)
		{
			int location = row * boardWidth + col; //for easier manipulation			
												   
			if (location >= 8 && location <= 15)
				pieces.push_back(std::shared_ptr<Pawn>(new Pawn(Vec2I{ col,row }, Team::BLACK, &board, new Surface(Surface::FromFile(BPawnSprite)))));
			else if (location >= 48 && location <= 55)
				pieces.push_back(std::shared_ptr<Pawn>(new Pawn(Vec2I{ col,row }, Team::WHITE, &board, new Surface(Surface::FromFile(WPawnSprite)))));
			else
			{
				switch (location)
				{
					case 0:
						pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ col,row }, Team::BLACK, &board, new Surface(Surface::FromFile(BRookSprite)))));
						break;
					case 1:
						pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ col,row }, Team::BLACK, &board, new Surface(Surface::FromFile(BKnightSprite)))));
						break;
					case 2:
						pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ col,row }, Team::BLACK, &board, new Surface(Surface::FromFile(BBishopSprite)))));
						break;
					case 3:
						pieces.push_back(std::shared_ptr<Queen>(new Queen(Vec2I{ col,row }, Team::BLACK, &board, new Surface(Surface::FromFile(BQueenSprite)))));
						break;
					case 4:
						pieces.push_back(std::shared_ptr<King>(new King(Vec2I{ col,row }, Team::BLACK, &board, new Surface(Surface::FromFile(BKingSprite)))));
						break;
					case 5:
						pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ col,row }, Team::BLACK, &board, new Surface(Surface::FromFile(BBishopSprite)))));
						break;
					case 6:
						pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ col,row }, Team::BLACK, &board, new Surface(Surface::FromFile(BKnightSprite)))));
						break;
					case 7:
						pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ col,row }, Team::BLACK, &board, new Surface(Surface::FromFile(BRookSprite)))));
						break;
					case 63 - 0:
						pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ col,row }, Team::WHITE, &board, new Surface(Surface::FromFile(WRookSprite)))));
						break;
					case 63 - 1:
						pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ col,row }, Team::WHITE, &board, new Surface(Surface::FromFile(WKnightSprite)))));
						break;
					case 63 - 2:
						pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ col,row }, Team::WHITE, &board, new Surface(Surface::FromFile(WBishopSprite)))));
						break;
					case 63 - 3:
						pieces.push_back(std::shared_ptr<Queen>(new Queen(Vec2I{ col,row }, Team::WHITE, &board, new Surface(Surface::FromFile(WQueenSprite)))));
						break;
					case 63 - 4:
						pieces.push_back(std::shared_ptr<King>(new King(Vec2I{ col,row }, Team::WHITE, &board, new Surface(Surface::FromFile(WKingSprite)))));
						break;
					case 63 - 5:
						pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ col,row }, Team::WHITE, &board, new Surface(Surface::FromFile(WBishopSprite)))));
						break;
					case 63 - 6:
						pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ col,row }, Team::WHITE, &board, new Surface(Surface::FromFile(WKnightSprite)))));
						break;
					case 63 - 7:
						pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ col,row }, Team::WHITE, &board, new Surface(Surface::FromFile(WRookSprite)))));
						break;
					default:
						break;
				}
			}
		}
	}
	//generate valid moves for all pieces
	for each (auto piece in pieces)
		piece->GenerateValidMoves(); 
}

std::shared_ptr<Piece> GameDirector::getPiece(Vec2I location, GlobalEnums::pieceType type, GlobalEnums::Team team) const
{
	for each (std::shared_ptr<Piece> p in pieces)
	{
		if (p->GetType() == type && p->GetTeam() == team && p->Locate() == location)
			return p;
	}
	return nullptr;
}

std::shared_ptr<Piece> GameDirector::getPiece(Vec2I location) const
{
	for each (auto p in pieces)
	{
		if (p->Locate() == location)
			return p;
	}
	return nullptr;
}

void GameDirector::SetStage(bool debugMode)
{
	if (debugMode)
	{
		board.DrawPieces(gfx);
	}
	else //release mode
	{
		board.DrawSprite(gfx);
		board.DrawPiecesSprite(gfx);
	}

	board.DrawGrid(gfx, Colors::LightGray, { 20,21 });
	if (selectionMode)
	{
		highlight = Colors::Magenta;
		if (selectedPiece != nullptr)
		{
			if (selectedPiece != nullptr)
			{
				auto p = selectedPiece->getValidTiles();
				board.HighlightTiles(gfx, p, Colors::Orange);
			}
		}
	}
	else
		highlight = Colors::Red;

	board.HighlightTile(gfx, mouse.GetPos(), highlight);
}

void GameDirector::HandleInput(bool cheatMode)
{
	static int clickCounter = 0;
	static std::shared_ptr<Tile> t1, t2;

	//do highlights
	if (clickCounter == 1)
		selectionMode = true;	

	const Mouse::Event e = mouse.Read();
	if (e.GetType() == Mouse::Event::LPress) //update counter on left click
	{
		if (clickCounter == 0) //first click
		{
			t1 = board.GetTileByMouse(mouse.GetPos()); //click 1 (get its coordinates)
			if (t1)
			{
				selectedPiece = getPiece(t1->location);
				if (selectedPiece)
					clickCounter++;
			}
			else
				selectedPiece = nullptr;
		}
		else if (clickCounter >= 1)
		{
			t2 = board.GetTileByMouse(mouse.GetPos()); //click 2 (get its coordinates)
			if (t1 != nullptr && t2 != nullptr && t1 != t2) //if the 2 clicks locations are valid
			{
				//move the piece (if its logical)
				auto pieceInT1 = getPiece(t1->location);

				//check cheating mode
				if (cheatMode)
				{
					if (pieceInT1 != nullptr)
					{
						if (pieceInT1->MoveTo(t2->location)) //if piece moved
							for each (auto piece in pieces)
								piece->GenerateValidMoves(); //generate valid moves for all pieces
					}
				}
				else //not cheatMode
				{					
					if (pieceInT1 != nullptr && WhoseTurn() == pieceInT1->GetTeam())
					{
						if (pieceInT1->MoveTo(t2->location)) //if moving succeed (if it actually moved!)
						{
							gameTurn++;	//turn ends
							for each (auto piece in pieces)
								piece->GenerateValidMoves(); //generate valid moves for all pieces								
							
						}
					}
				}
				
			}
			clickCounter = 0;
			selectionMode = false;
		}
	}
}

std::shared_ptr<Piece> GameDirector::Transformed(Piece* p)
{	
	assert(dynamic_cast<Pawn*> (p) != nullptr);
	auto location = p->Locate();
	if (p->GetTeam() == Team::BLACK)
	{
		pieces.push_back(std::shared_ptr<Queen>(new Queen(Vec2I{ location }, Team::BLACK, &board, new Surface(Surface::FromFile(BQueenSprite)))));
	}
	else if (p->GetTeam() == Team::WHITE)
	{
		pieces.push_back(std::shared_ptr<Queen>(new Queen(Vec2I{ location }, Team::WHITE, &board, new Surface(Surface::FromFile(WQueenSprite)))));
	}
	DestroyPiece(p);
	//generate valid moves for all pieces
	for each (auto piece in pieces)
		piece->GenerateValidMoves();
	return *(pieces.end() - 1); //pointer to the new piece
}

bool GameDirector::DestroyPiece(Piece* piece)
{
	for (auto itr = pieces.begin(); itr < pieces.end(); itr++)
	{
		if ((*itr)->Locate() == piece->Locate())
		{
			pieces.erase(itr);
			return true; //success
		}
	}
	return false; //failure
}

bool GameDirector::DestroyPiece(std::shared_ptr<Piece> piece)
{
	for (auto itr = pieces.begin(); itr < pieces.end(); itr++)
	{
		if ((*itr)->Locate() == piece->Locate())
		{
			pieces.erase(itr);
			return true; //success
		}
	}
	return false; //failure
}

//cheating functions 
