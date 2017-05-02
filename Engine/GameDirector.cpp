#include "GameDirector.h"
#include "Board.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"



#define WPawnSprite    L"Resources\\Chess Pieces\\Wood\\PawnW.png"
#define BPawnSprite    L"Resources\\Chess Pieces\\Wood\\PawnB.png"
#define WRookSprite    L"Resources\\Chess Pieces\\Wood\\RookW.png"
#define BRookSprite    L"Resources\\Chess Pieces\\Wood\\RookB.png"
#define WKnightSprite  L"Resources\\Chess Pieces\\Wood\\KnightW.png"
#define BKnightSprite  L"Resources\\Chess Pieces\\Wood\\KnightB.png"
#define WBishopSprite  L"Resources\\Chess Pieces\\Wood\\BishopW.png"
#define BBishopSprite  L"Resources\\Chess Pieces\\Wood\\BishopB.png"
#define WQueenSprite   L"Resources\\Chess Pieces\\Wood\\QueenW.png"
#define BQueenSprite   L"Resources\\Chess Pieces\\Wood\\QueenB.png"
#define WKingSprite    L"Resources\\Chess Pieces\\Wood\\KingW.png"
#define BKingSprite    L"Resources\\Chess Pieces\\Wood\\KingB.png"

#define WPromotionScreen L"Resources\\Screens\\Promotion Screen Wood White.png"
#define BPromotionScreen L"Resources\\Screens\\Promotion Screen Wood Black.png"

std::wstring GetPieceSprite(pieceType type , Team team)
{
	if (team == Team::BLACK)
	{
		switch (type)
		{
			case GlobalEnums::PAWN:
				return BPawnSprite;
			case GlobalEnums::KNIGHT:
				return BKnightSprite;
			case GlobalEnums::ROOK:
				return BRookSprite;
			case GlobalEnums::BISHOP:
				return BBishopSprite;
			case GlobalEnums::QUEEN:
				return BQueenSprite;
			case GlobalEnums::KING:
				return BKingSprite;
			case GlobalEnums::NOT_DEFINED:
				return L"NOT_DEFINED";
			default:
				break;
		}
	}
	else if (team == Team::WHITE)
	{
		switch (type)
		{
			case GlobalEnums::PAWN:
				return WPawnSprite;
			case GlobalEnums::KNIGHT:
				return WKnightSprite;
			case GlobalEnums::ROOK:
				return WRookSprite;
			case GlobalEnums::BISHOP:
				return WBishopSprite;
			case GlobalEnums::QUEEN:
				return WQueenSprite;
			case GlobalEnums::KING:
				return WKingSprite;
			case GlobalEnums::NOT_DEFINED:
				return L"NOT_DEFINED";
			default:
				break;
		}
	}
	else
	{
		return L"ERROR";
	}
}

GameDirector::GameDirector(Board &board,Graphics &gfx, Mouse &mouse)
	:
	board(board),
	gfx(gfx),
	mouse(mouse),
	font(L"times", 20.0f),
	BpromotionScreen(new Surface(Surface::FromFile(BPromotionScreen))),
	WpromotionScreen(new Surface(Surface::FromFile(WPromotionScreen)))
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
	GenerateMovesForAllPieces();
	BKingLoc = getPiece(KING, Team::BLACK)->Locate();
	WKingLoc = getPiece(KING, Team::WHITE)->Locate();
}

GameDirector::GameDirector(Board & board, Graphics & gfx, Mouse & mouse, std::string saveFile)
	:
	board(board),
	gfx(gfx),
	mouse(mouse),
	font(L"times", 20.0f),
	BpromotionScreen(new Surface(Surface::FromFile(BPromotionScreen))),
	WpromotionScreen(new Surface(Surface::FromFile(WPromotionScreen)))
{
	LoadGame(saveFile);
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

std::shared_ptr<Piece> GameDirector::getPiece(GlobalEnums::pieceType type, GlobalEnums::Team team) const
{
	for each (std::shared_ptr<Piece> p in pieces)
	{
		if (p->GetType() == type && p->GetTeam() == team)
			return p;
	}
	return nullptr;
}

bool GameDirector::IsTileUnderThreatBy(Vec2I TileLocation, GlobalEnums::Team ThreatningTeam)
{
	for (auto i = pieces.begin(); i < pieces.end(); i++)
	{
		auto p = i->get();
		for each (auto validTile in p->getValidTiles())
		{
			//if the piece can move to that tile and it is from enemy team (meaning tile is underThreat)
			if (TileLocation == validTile && p->GetTeam() == ThreatningTeam) 
				return true;
		}
	}
	return false;
}

bool GameDirector::AreTilesUnderThreat(std::vector<Vec2I> Tileslocations, GlobalEnums::Team ThreatningTeam)
{
	for (auto i = Tileslocations.begin(); i < Tileslocations.end(); i++)
	{
		if (IsTileUnderThreatBy(*i, ThreatningTeam))
			return true;
	}
	return false;
}

void GameDirector::EnterPromotionMode(Piece * p)
{
	if (dynamic_cast<Pawn*> (p))
	{
		promotionMode = true;
		luckyPawn = dynamic_cast<Pawn*> (p);
	}
}

void GameDirector::RerollTurn(std::shared_ptr<Piece> piece)
{
	gameTurn--;
	piece->UndoMove();
	GenerateMovesForAllPieces();
	CheckKingsSafety();
}

void GameDirector::SaveGame(std::string saveFile)
{
	using namespace std;
	//open file
	ofstream file(saveFile);

	//save operation
	for each (auto piece in pieces)
	{		
		string type(GetTextForpieceType(piece->GetType()));
		string team(GetTextForTeam((int)piece->GetTeam()));
		string location(to_string(piece->Locate().x) + ' '+ to_string(piece->Locate().y));
		string nStepsMoved;
		if (dynamic_pointer_cast<Pawn> (piece))
			nStepsMoved = to_string(dynamic_pointer_cast<Pawn> (piece)->nStepsMoved());
		else
			nStepsMoved = '0';

		string line(type + ' ' + team + ' ' + location + ' ' + nStepsMoved );
		file << line << " \n" ;
	}	
	file.close();
}

void GameDirector::QuickSaveGame()
{
	SaveGame("../Quick Save.txt");
}

void GameDirector::LoadGame(std::string saveFile)
{	
	using namespace std;
	//open file
	ifstream loadFile(saveFile);
	//check if its there
	if (loadFile)
	{
		//clear remove all pieces from the game
		pieces.clear();
		board.ResetAllTiles();		
		string type,team,locationX, locationY,nStepsMoved;
		int round = 0;
	
		//Read operation
		while (loadFile)
		{
			if (round == 0)
				loadFile >> type;
			else if (round == 1)
				loadFile >> team;
			else if (round == 2)
				loadFile >> locationX;
			else if (round == 3)
				loadFile >> locationY;
			else if (round == 4)
				loadFile >> nStepsMoved;
			round++;
			//means we got all the data we want
			if (round > 4)
			{
				int x = std::stoi(locationX);
				int y = std::stoi(locationY);
				int steps = std::stoi(nStepsMoved);
				auto Team = GetTeamFromText(team);
				auto pieceType = GetPieceTypeFromText(type);
				//check type
				switch (pieceType)
				{
					case GlobalEnums::PAWN:
						pieces.push_back(std::shared_ptr<Pawn>(new Pawn(Vec2I{ x,y }, Team, &board, new Surface(Surface::FromFile(GetPieceSprite(pieceType, Team))), steps)));
						break;
					case GlobalEnums::KNIGHT:
						pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ x,y }, Team, &board, new Surface(Surface::FromFile(GetPieceSprite(pieceType, Team))))));
						break;
					case GlobalEnums::ROOK:
						pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ x,y }, Team, &board, new Surface(Surface::FromFile(GetPieceSprite(pieceType, Team))))));
						break;
					case GlobalEnums::BISHOP:
						pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ x,y }, Team, &board, new Surface(Surface::FromFile(GetPieceSprite(pieceType, Team))))));
						break;
					case GlobalEnums::QUEEN:
						pieces.push_back(std::shared_ptr<Queen>(new Queen(Vec2I{ x,y }, Team, &board, new Surface(Surface::FromFile(GetPieceSprite(pieceType, Team))))));
						break;
					case GlobalEnums::KING:
						pieces.push_back(std::shared_ptr<King>(new King(Vec2I{ x,y }, Team, &board, new Surface(Surface::FromFile(GetPieceSprite(pieceType, Team))))));
						break;
					case GlobalEnums::NOT_DEFINED:
						break;
					default:
						break;
				}
				round = 0;
			}
		}
		GenerateMovesForAllPieces();
		BKingLoc = getPiece(KING, Team::BLACK)->Locate();
		WKingLoc = getPiece(KING, Team::WHITE)->Locate();
		loadFile.close();
	}
}

void GameDirector::QuickLoadGame()
{
	LoadGame("../Quick Save.txt");
}

void GameDirector::MarkForDestruction(std::shared_ptr<Piece> pieceToDestroy)
{
	this->pieceToDestroy = pieceToDestroy;
}

void GameDirector::RemoveDestructionMark()
{
	pieceToDestroy = nullptr;
}

void GameDirector::DestroyMarkedPiece()
{
	if(pieceToDestroy)
		DestroyPiece(pieceToDestroy);
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
	if (promotionMode)
	{
		DrawPawnPromotionScreen(mouse.GetPos(), luckyPawn->GetTeam(), Colors::Green, Colors::Black);
	}
	else
	{
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
	//DrawStartMenu(mouse.GetPos());
}

void GameDirector::DrawStartMenu(Vec2I mousePos)
{
	//screen background coordinates
	static Vec2I topLeft{ 0,0 };
	static Vec2I botRight{ (int) Graphics::ScreenWidth,(int)Graphics::ScreenHeight };

	//buttons
	static Button startBtn({ (int)(Graphics::ScreenWidth / 2 - 80.0),(int)(Graphics::ScreenHeight / 2 + 30) } ,100,50,L"Start" );

	//drawing
	for ( int x = topLeft.x; x < botRight.x; x++)
	{
		for ( int y = topLeft.y; y < botRight.y; y++)
		{
			gfx.PutPixel(x, y, Colors::Black);
		}
	}

	if(startBtn.GetBoundingBox().Contains(mousePos))
		startBtn.Draw(gfx, font, 15,10,Colors::Red);
	else
		startBtn.Draw(gfx, font, 15, 10, Colors::Green);


}

void GameDirector::DrawPawnPromotionScreen(Vec2I mousPos, GlobalEnums::Team team ,Color edgesClr, Color highlightClr)
{
	static Vec2I topLeft{ 20 + 340 - 179,20 + 340 - 99 };
	static Vec2I botRight{ topLeft.x + 79 * 4,topLeft.y + 79 };

	if (team == Team::BLACK)
	{
		int xPieceSpr = 0;
		int yPieceSpr = 0;
		for (unsigned int x = topLeft.x; x < BpromotionScreen->GetWidth() + topLeft.x; x++)
		{
			for (unsigned int y = topLeft.y; y < BpromotionScreen->GetHeight() + topLeft.y; y++)
			{				
				gfx.PutPixelAlphaClipped(x, y, BpromotionScreen->GetPixel(xPieceSpr, yPieceSpr), RectI(0, Graphics::ScreenHeight, 0, Graphics::ScreenWidth));
				yPieceSpr++;
			}
			xPieceSpr++;
			yPieceSpr = 0;
		}
	}
	else if (team == Team::WHITE)
	{
		int xPieceSpr = 0;
		int yPieceSpr = 0;
		for (unsigned int x = topLeft.x; x < WpromotionScreen->GetWidth() + topLeft.x; x++)
		{
			for (unsigned int y = topLeft.y; y < WpromotionScreen->GetHeight() + topLeft.y; y++)
			{				
				gfx.PutPixelAlphaClipped(x, y, WpromotionScreen->GetPixel(xPieceSpr, yPieceSpr), RectI(0, Graphics::ScreenHeight, 0, Graphics::ScreenWidth));
				yPieceSpr++;
			}
			xPieceSpr++;
			yPieceSpr = 0;
		}
	}

	static RectI rook	({ topLeft.x 		 , topLeft.y }, { topLeft.x + 80	 , botRight.y });
	static RectI knight ({ topLeft.x + 80	 , topLeft.y }, { topLeft.x + 80 * 2 , botRight.y });
	static RectI bishop ({ topLeft.x + 80 * 2, topLeft.y }, { topLeft.x + 80 * 3 , botRight.y });
	static RectI queen	({ topLeft.x + 80 * 3, topLeft.y }, { topLeft.x + 80 * 4 , botRight.y });
	promotionRects = { rook,knight,bishop,queen };

	gfx.DrawTextW(L"Choose The Type of promotion", {(float) topLeft.x - 20.0f,(float)topLeft.y - 40.0f }, font, highlightClr);
	// check if mouse is inside any rect
	for each (auto rec in promotionRects)
	{
		if (rec.Contains(mousPos))
			gfx.DrawRect(rec, highlightClr);
		else
			gfx.DrawRect(rec, edgesClr);
	}
}

void GameDirector::HandleInput(bool cheatMode)
{
	if (promotionMode)
	{
		const Mouse::Event e = mouse.Read();
		if (e.GetType() == Mouse::Event::LPress)
		{
			
			int loopCounter = 0;
			for each (auto rec in promotionRects)
			{
				if (rec.Contains(mouse.GetPos()))
				{
					switch (loopCounter)
					{
						case 0:
							PromoteTo(ROOK);
							promotionMode = false;
							break;
						case 1:
							PromoteTo(KNIGHT);
							promotionMode = false;
							break;
						case 2:
							PromoteTo(BISHOP);
							promotionMode = false;
							break;
						case 3:
							PromoteTo(QUEEN);
							promotionMode = false;
							break;
					}
				}
				loopCounter++;
			}
		}
	}
	else 
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
					auto pieceInT2 = getPiece(t2->location);

					//check cheating mode
					if (cheatMode)
					{
						if (AreKingsSafe())
						{
							if (pieceInT1 != nullptr)
							{
								if (pieceInT1->MoveTo(t2->location)) //if piece moved
								{
									//do turn
									gameTurn++;
									GenerateMovesForAllPieces();
									CheckKingsSafety();

									if ((WkingUnderThreat && pieceInT1->GetTeam() == Team::WHITE) ||
										(BkingUnderThreat && pieceInT1->GetTeam() == Team::BLACK))
									{ //prevent player from putting his king in danger

										RerollTurn(pieceInT1);
									}
								}
								else if (DoCastling(pieceInT1, pieceInT2))
								{
									gameTurn++;
									GenerateMovesForAllPieces();
									CheckKingsSafety();
									if ((WkingUnderThreat && pieceInT1->GetTeam() == Team::WHITE) ||
										(BkingUnderThreat && pieceInT1->GetTeam() == Team::BLACK))
									{ //prevent player from putting his king in danger
										RerollTurn(pieceInT1);
									}
								}
								else if (DoEnPassant(pieceInT1, t2))
								{
									gameTurn++;
									GenerateMovesForAllPieces();
									CheckKingsSafety();

									if ((WkingUnderThreat && pieceInT1->GetTeam() == Team::WHITE) ||
										(BkingUnderThreat && pieceInT1->GetTeam() == Team::BLACK))
									{ //prevent player from putting his king in danger
										RerollTurn(pieceInT1);
									}
								}
							}
						}
						else //king is already under threat
						{
							//block moves if it doesn't remove threats
							if (pieceInT1 != nullptr)
							{
								if (pieceInT1->MoveTo(t2->location)) //if piece moved
								{
									gameTurn++;
									GenerateMovesForAllPieces();
									CheckKingsSafety();
									if (!AreKingsSafe())
									{
										RerollTurn(pieceInT1);
									}
								}
								else if (DoCastling(pieceInT1, pieceInT2))
								{
									gameTurn++;
									GenerateMovesForAllPieces();
									CheckKingsSafety();
									if (!AreKingsSafe())
									{
										RerollTurn(pieceInT1);
									}
								}
								else if (DoEnPassant(pieceInT1, t2))
								{									
									gameTurn++;
									GenerateMovesForAllPieces();
									CheckKingsSafety();
									if ((WkingUnderThreat && pieceInT1->GetTeam() == Team::WHITE) ||
										(BkingUnderThreat && pieceInT1->GetTeam() == Team::BLACK))
									{ //prevent player from putting his king in danger
										RerollTurn(pieceInT1);
									}
								}
							}

						}
					}
					else //not cheatMode
					{
						if (AreKingsSafe())
						{
							if (pieceInT1 != nullptr && WhoseTurn() == pieceInT1->GetTeam())
							{
								if (pieceInT1->MoveTo(t2->location)) //if moving succeed (if it actually moved!)
								{
									//do turn
									gameTurn++;	//turn ends
									GenerateMovesForAllPieces();
									CheckKingsSafety();

									if ((WkingUnderThreat && pieceInT1->GetTeam() == Team::WHITE) ||
										(BkingUnderThreat && pieceInT1->GetTeam() == Team::BLACK))
									{ //prevent player from putting his king in danger
										RerollTurn(pieceInT1);
									}
								}
								else if (DoCastling(pieceInT1, pieceInT2))
								{
									gameTurn++;	//turn ends
									GenerateMovesForAllPieces();
									CheckKingsSafety();

									if ((WkingUnderThreat && pieceInT1->GetTeam() == Team::WHITE) ||
										(BkingUnderThreat && pieceInT1->GetTeam() == Team::BLACK))
									{ //prevent player from putting his king in danger
										RerollTurn(pieceInT1);
									}
								}
								else if (DoEnPassant(pieceInT1, t2))
								{
									gameTurn++;	//turn ends
									GenerateMovesForAllPieces();
									CheckKingsSafety();
									if ((WkingUnderThreat && pieceInT1->GetTeam() == Team::WHITE) ||
										(BkingUnderThreat && pieceInT1->GetTeam() == Team::BLACK))
									{ //prevent player from putting his king in danger
										RerollTurn(pieceInT1);
									}
								}
							}
							
						}
						else //king is already under threat
						{
							if (pieceInT1 != nullptr && WhoseTurn() == pieceInT1->GetTeam())
							{
								if (pieceInT1->MoveTo(t2->location)) //if moving succeed (if it actually moved!)
								{
									//do turn
									gameTurn++;	//turn ends
									GenerateMovesForAllPieces();
									CheckKingsSafety();

									if (!AreKingsSafe())
									{ //prevent player from putting his king in danger
										RerollTurn(pieceInT1);
									}
								}
								else if (DoCastling(pieceInT1, pieceInT2))
								{
									gameTurn++;	//turn ends
									GenerateMovesForAllPieces();
									CheckKingsSafety();
									if (!AreKingsSafe())
									{ //prevent player from putting his king in danger
										RerollTurn(pieceInT1);
									}
								}
								else if (DoEnPassant(pieceInT1, t2))
								{
									gameTurn++;	//turn ends
									GenerateMovesForAllPieces();
									CheckKingsSafety();
									if ((WkingUnderThreat && pieceInT1->GetTeam() == Team::WHITE) ||
										(BkingUnderThreat && pieceInT1->GetTeam() == Team::BLACK))
									{ //prevent player from putting his king in danger
										RerollTurn(pieceInT1);
									}
								}
							}
							
						}
					}

					DestroyMarkedPiece();
					CheckForEnPassants();
				}
				clickCounter = 0;
				selectionMode = false;
			}
		}
	}
}

void GameDirector::PromoteTo(GlobalEnums::pieceType type)
{	
	auto location = luckyPawn->Locate();
	if (luckyPawn->GetTeam() == Team::BLACK)
	{
		switch (type)
		{
			case GlobalEnums::KNIGHT:
				pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ location }, Team::BLACK, &board, new Surface(Surface::FromFile(BKnightSprite)))));
				break;
			case GlobalEnums::ROOK:
				pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ location }, Team::BLACK, &board, new Surface(Surface::FromFile(BRookSprite)))));
				break;
			case GlobalEnums::BISHOP:
				pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ location }, Team::BLACK, &board, new Surface(Surface::FromFile(BBishopSprite)))));
				break;
			case GlobalEnums::QUEEN:
				pieces.push_back(std::shared_ptr<Queen>(new Queen(Vec2I{ location }, Team::BLACK, &board, new Surface(Surface::FromFile(BQueenSprite)))));
				break;
		}
	}
	else if (luckyPawn->GetTeam() == Team::WHITE)
	{
		switch (type)
		{
			case GlobalEnums::KNIGHT:
				pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ location }, Team::WHITE, &board, new Surface(Surface::FromFile(WKnightSprite)))));
				break;
			case GlobalEnums::ROOK:
				pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ location }, Team::WHITE, &board, new Surface(Surface::FromFile(WRookSprite)))));
				break;
			case GlobalEnums::BISHOP:
				pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ location }, Team::WHITE, &board, new Surface(Surface::FromFile(WBishopSprite)))));
				break;
			case GlobalEnums::QUEEN:
				pieces.push_back(std::shared_ptr<Queen>(new Queen(Vec2I{ location }, Team::WHITE, &board, new Surface(Surface::FromFile(WQueenSprite)))));
				break;
		}
	}
	DestroyPiece(luckyPawn);
	GenerateMovesForAllPieces();
	CheckKingsSafety();
}

bool GameDirector::DoCastling(std::shared_ptr<Piece> piece1, std::shared_ptr<Piece> piece2)
{
	std::shared_ptr<King> king;
	std::shared_ptr<Rook> rook;
	if (std::dynamic_pointer_cast<King> (piece1) && piece1->GetType() == KING)
	{
		king = std::dynamic_pointer_cast<King> (piece1);
		if (std::dynamic_pointer_cast<Rook> (piece2) && piece2->GetType() == ROOK)
			rook = std::dynamic_pointer_cast<Rook> (piece2);
		else //neither one of them is rook
			return false;
	}
	else if (std::dynamic_pointer_cast<King> (piece2) && piece2->GetType() == KING)
	{
		king = std::dynamic_pointer_cast<King> (piece2);
		if (std::dynamic_pointer_cast<Rook> (piece1) && piece1->GetType() == ROOK)
			rook = std::dynamic_pointer_cast<Rook> (piece1);
		else //neither one of them is rook
			return false;
	}
	else //neither one of them is king
		return false;

	if ((king->GetTeam() == rook->GetTeam()) &&
		!king->HasMovedBefore() && !rook->HasMovedBefore()) //if it is king and rook and same team and they didn't move before
	{
		//start from left to right
		int start = min(king->Locate().x, rook->Locate().x) + 1;
		int end = max(king->Locate().x, rook->Locate().x);
		int y = king->Locate().y;
		bool valid = true;
		for (int x = start; x < end; x++)
		{
			//check if tiles in between got any pieces
			auto s = board.GetTileState({ x,y }).containPiece;
			auto s2 = IsTileUnderThreatBy({ x,y },piece1->GetEnemyTeam());
			//if (board.GetTileState({ x,y }).containPiece || IsTileUnderThreat({ x,y }))  //should check for threats from any other piece
			if(s || s2)
			{
				valid = false;
				break;
			}
		}
		if (valid)
		{
			if (king->Locate().x < rook->Locate().x) //means rook is on the right
			{//t2 rook
				king->PutAt({ king->Locate().x + 2,y });
				rook->PutAt({ king->Locate().x - 1,y });
				return true;
			}
			else //rook is on left
			{
				king->PutAt({ king->Locate().x - 2,y });
				rook->PutAt({ king->Locate().x + 1,y });
				return true;
			}
		}
		else
			return false;
	}
	else
		return false;
}

bool GameDirector::DoEnPassant(std::shared_ptr<Piece> piece, std::shared_ptr<Tile> tile)
{
	if (std::dynamic_pointer_cast<Pawn>(piece))
	{
		auto pawn = std::dynamic_pointer_cast<Pawn>(piece);
		if (std::find(pawn->getValidTiles().begin(), pawn->getValidTiles().end(), tile->location) != pawn->getValidTiles().end()) //if its valid tile
		{
			if (pawn->PutAt(tile->location))
			{
				if (pawn->GetTeam() == Team::WHITE)
				{
					DestroyPiece(getPiece({ tile->location.x , tile->location.y + 1 })); // +1 is for case the pawn being destroyed is BLACK
					board.ResetTile({ tile->location.x , tile->location.y + 1 });
				}
				else if (pawn->GetTeam() == Team::BLACK)
				{
					DestroyPiece(getPiece({ tile->location.x , tile->location.y - 1 })); // -1 is for case the pawn being destroyed is BLACK
					board.ResetTile({ tile->location.x , tile->location.y - 1 });
				}
				else
					return false;

				return true;
			}
			else
				return false; //couldn't put
		}
		else //not valid tile
			return false;
		
	}
	else
		return false; //not pawn
}

void GameDirector::CheckForEnPassants()
{
	//check the turn
	static int turnRegistered;
	static std::vector<Vec2I> checkedLocations; //locations checked for defeneding pawns
	static int blackPawnsRow = 1;
	static int blackPawnsRiskyRow = blackPawnsRow + 2;
	static int whitePawnsRow = 6;
	static int whitePawnsRiskyRow = whitePawnsRow - 2;
	std::shared_ptr<Pawn> defendingPawn;

	if (gameTurn - turnRegistered >= 1)
		turnRegistered = -2;

	bool checkedBefore;
	for (int x = 0; x < board_columns; x++)
	{
		
		//from left to right
		//this section is for black rows
		checkedBefore = std::find(checkedLocations.begin(), checkedLocations.end(), Vec2I(x,blackPawnsRow)) != checkedLocations.end();
		if (checkedBefore )
		{//&& (tile.containPiece && tile.piecetype == PAWN && tile.pieceTeam == Team::BLACK)
			continue;
		}
		else //not all pawns in location or its newly empty place
		{
			//get the pawn which moved

			if (getPiece({ x, blackPawnsRiskyRow }, PAWN, Team::BLACK))
			{
				defendingPawn = std::dynamic_pointer_cast<Pawn>(getPiece({ x, blackPawnsRiskyRow }));
				if (defendingPawn->nStepsMoved() == 2) //jumped
				{
					//check its right and left for an offensor
					Vec2I leftTileLocation = { x - 1,blackPawnsRiskyRow };
					Vec2I rightTileLocation = { x + 1,blackPawnsRiskyRow };
					auto leftTile = board.GetTileState(leftTileLocation);
					auto rightTile = board.GetTileState(rightTileLocation);

					if (leftTile.containPiece && leftTile.piecetype == PAWN && leftTile.pieceTeam == Team::WHITE)
					{
						//this piece is offensor
						getPiece(leftTileLocation)->AddValidTile({ x,blackPawnsRiskyRow - 1 });
						turnRegistered = gameTurn;
						checkedLocations.push_back({ x,blackPawnsRow });
						return; //all conditions are met for registering an enpassant case
					}
					if (rightTile.containPiece && rightTile.piecetype == PAWN && rightTile.pieceTeam == Team::WHITE)
					{
						//this piece is offensor
						getPiece(rightTileLocation)->AddValidTile({ x,blackPawnsRiskyRow - 1 });
						turnRegistered = gameTurn;
						checkedLocations.push_back({ x,blackPawnsRow });
						return; //all conditions are met for registering an enpassant case
					}
					return;//nothing to its left or right

				}
				else //not jump
					return;
			}
			else
				continue; //the pawn is gone forever , check the rest of the row
		}
	}

	//=====================================================================
	//this section is for white rows

	for (int x = 0; x < board_columns; x++)
	{
		checkedBefore = std::find(checkedLocations.begin(), checkedLocations.end(), Vec2I(x, whitePawnsRow)) != checkedLocations.end();
		if (checkedBefore)
		{//&& (tile.containPiece && tile.piecetype == PAWN && tile.pieceTeam == Team::BLACK)
			continue;
		}
		else //not all pawns in location or its newly empty place
		{
			//get the pawn which moved

			if (getPiece({ x, whitePawnsRiskyRow }, PAWN, Team::WHITE))
			{
				defendingPawn = std::dynamic_pointer_cast<Pawn>(getPiece({ x, whitePawnsRiskyRow }));
				if (defendingPawn->nStepsMoved() == 2) //jumped
				{
					//check its right and left for an offensor
					Vec2I leftTileLocation = { x - 1,whitePawnsRiskyRow };
					Vec2I rightTileLocation = { x + 1,whitePawnsRiskyRow };
					auto leftTile = board.GetTileState(leftTileLocation);
					auto rightTile = board.GetTileState(rightTileLocation);

					if (leftTile.containPiece && leftTile.piecetype == PAWN && leftTile.pieceTeam == Team::BLACK)
					{
						//this piece is offensor
						getPiece(leftTileLocation)->AddValidTile({ x,whitePawnsRiskyRow + 1 });
						turnRegistered = gameTurn;
						checkedLocations.push_back({ x,whitePawnsRow });
						return; //all conditions are met for registering an enpassant case
					}
					if (rightTile.containPiece && rightTile.piecetype == PAWN && rightTile.pieceTeam == Team::BLACK)
					{
						//this piece is offensor
						getPiece(rightTileLocation)->AddValidTile({ x,whitePawnsRiskyRow + 1 });
						turnRegistered = gameTurn;
						checkedLocations.push_back({ x,whitePawnsRow });
						return; //all conditions are met for registering an enpassant case
					}
					return;//nothing to its left or right

				}
				else //not jump
					return;
			}
			else
				continue; //the pawn is gone forever , check the rest of the row
		}
	}
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
		if ((*itr)->Locate() == piece->Locate() && (*itr)->GetTeam() == piece->GetTeam() && (*itr)->GetType() == piece->GetType())
		{
			pieces.erase(itr);
			return true; //success
		}
	}
	return false; //failure
}

void GameDirector::GenerateMovesForAllPieces()
{
	//first we generate valid moves for all pieces
	for each (auto piece in pieces)
	{
		piece->GenerateValidMoves();	
	}
}

void GameDirector::CheckKingsSafety()
{
	for each (auto piece in pieces)
	{
		//check if any king under threat
		for (auto itr = piece->getValidTiles().begin(); itr < piece->getValidTiles().end(); itr++)
		{
			if (*itr == BKingLoc)
			{
				BkingUnderThreat = true;
				threatningPiece = piece;
				return;
			}
			else if (*itr == WKingLoc)
			{
				WkingUnderThreat = true;
				threatningPiece = piece;
				return;
			}
		}
		//if we reached this point, then there is none under threat
		WkingUnderThreat = false;
		BkingUnderThreat = false;
		threatningPiece = nullptr;
	}
}


//cheating functions 
