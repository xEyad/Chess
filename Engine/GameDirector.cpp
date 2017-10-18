#include "GameDirector.h"

GameDirector::GameDirector(Board &board)
	:
	board(board)
{
	//spawn the pieces
	int boardWidth = board.rows;
	for (int row = 0; row < board.rows; row++)
	{
		for (int col = 0; col < board.columns; col++)
		{
			int location = row * boardWidth + col; //for easier manipulation			
												   
			if (location >= 8 && location <= 15)
				pieces.push_back(std::shared_ptr<Pawn>(new Pawn(Vec2I{ col,row }, Team::BLACK, &board)));
			else if (location >= 48 && location <= 55)
				pieces.push_back(std::shared_ptr<Pawn>(new Pawn(Vec2I{ col,row }, Team::WHITE, &board )));
			else
			{
				switch (location)
				{
					case 0:
						pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ col,row }, Team::BLACK, &board )));
						break;
					case 1:
						pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ col,row }, Team::BLACK, &board )));
						break;
					case 2:
						pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ col,row }, Team::BLACK, &board )));
						break;
					case 3:
						pieces.push_back(std::shared_ptr<Queen>(new Queen(Vec2I{ col,row }, Team::BLACK, &board )));
						break;
					case 4:
						pieces.push_back(std::shared_ptr<King>(new King(Vec2I{ col,row }, Team::BLACK, &board )));
						break;
					case 5:
						pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ col,row }, Team::BLACK, &board)));
						break;
					case 6:
						pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ col,row }, Team::BLACK, &board )));
						break;
					case 7:
						pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ col,row }, Team::BLACK, &board )));
						break;
					case 63 - 0:
						pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ col,row }, Team::WHITE, &board )));
						break;
					case 63 - 1:
						pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ col,row }, Team::WHITE, &board )));
						break;
					case 63 - 2:
						pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ col,row }, Team::WHITE, &board )));
						break;
					case 63 - 4:
						pieces.push_back(std::shared_ptr<Queen>(new Queen(Vec2I{ col,row }, Team::WHITE, &board )));
						break;
					case 63 - 3:
						pieces.push_back(std::shared_ptr<King>(new King(Vec2I{ col,row }, Team::WHITE, &board )));
						break;
					case 63 - 5:
						pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ col,row }, Team::WHITE, &board )));
						break;
					case 63 - 6:
						pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ col,row }, Team::WHITE, &board )));
						break;
					case 63 - 7:
						pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ col,row }, Team::WHITE, &board )));
						break;
					default:
						break;
				}
			}
		}
	}
	
	//intialize board tiles
	for each (auto piece  in pieces)	
		board.PutPieceOnTile( piece->Locate(), piece);
	
	GenerateMovesForAllPieces();
	BKingLoc = getPiece(KING, Team::BLACK)->Locate();
	WKingLoc = getPiece(KING, Team::WHITE)->Locate();
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

const std::vector<std::shared_ptr<Piece>>* GameDirector::getPieces() const
{
	return &pieces;
}


GameDirector::DirectorEvent GameDirector::ReadEvent()
{
	if (IsThereEvents())
	{
		DirectorEvent e = gameEvents.front();
		gameEvents.pop();
		return e;
	}
	else
		return DirectorEvent();
}

bool GameDirector::IsThereEvents() const
{
	if(gameEvents.size() > 0u)
		return true;
	else
		return false;
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
		luckyPawn = dynamic_cast<Pawn*> (p);
	}
}

bool GameDirector::WillKingBeDead(std::shared_ptr<Piece> movingPiece) const
{
	return (WkingUnderThreat && movingPiece->GetTeam() == Team::WHITE) ||
		(BkingUnderThreat && movingPiece->GetTeam() == Team::BLACK);
}

void GameDirector::RerollTurn(std::shared_ptr<Piece> piece)
{
	piece->UndoMove();
	board.PutPieceOnTile(piece->Locate(), piece);
	GenerateMovesForAllPieces();
	CheckKingsSafety();
}

void GameDirector::ChangeGamePieces(std::vector<std::shared_ptr<Piece>> newPieces)
{
	pieces.clear();
	pieces = newPieces;
	for each (auto piece in pieces)
		board.PutPieceOnTile(piece->Locate(), piece); //re-intialize board
	GenerateMovesForAllPieces();
	BKingLoc = getPiece(KING, Team::BLACK)->Locate();
	WKingLoc = getPiece(KING, Team::WHITE)->Locate();
	CheckKingsSafety();
}

void GameDirector::MarkForDestruction(std::shared_ptr<Piece> pieceToDestroy)
{
	this->pieceToDestroy = pieceToDestroy;
	pieceToDestroy->ClearValideTiles();
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

bool GameDirector::MovePiece(std::shared_ptr<Piece> piece, Vec2I Location)
{
	//move piece
	if (piece->MoveTo(Location))
	{
		ReflectChangesToBoard(piece);
		return true;
	}
	else
		return false;
}

bool GameDirector::PutPieceAt(std::shared_ptr<Piece> piece, Vec2I Location)
{
	if (piece->PutAt(Location))
	{
		ReflectChangesToBoard(piece);
		return true;
	}
	return false;
}

void GameDirector::HandleInput(const Vec2I tile1Location, const Vec2I tile2Location,const GlobalEnums::Team teamToPlay, const int gameTurn )
{	
	if (tile1Location != tile2Location) //if the 2 clicks locations are valid
	{
		//move the piece (if its logical)
		auto pieceInT1 = getPiece(tile1Location);
		auto pieceInT2 = getPiece(tile2Location);

		if (AreKingsSafe())
		{
			if (pieceInT1 != nullptr && teamToPlay == pieceInT1->GetTeam())
			{
				if (MovePiece(pieceInT1,tile2Location)) //if moving succeed (if it actually moved!)
				{
					//do turn					
					gameEvents.push(DirectorEvent::TurnPassed);
					GenerateMovesForAllPieces();
					CheckKingsSafety();

					if (WillKingBeDead(pieceInT1))
					{ //prevent player from putting his king in danger
						RerollTurn(pieceInT1);
						gameEvents.pop();
					}
				}
				else if (DoCastling(pieceInT1, pieceInT2))
				{
					gameEvents.push(DirectorEvent::TurnPassed);
					GenerateMovesForAllPieces();
					CheckKingsSafety();

					if (WillKingBeDead(pieceInT1))
					{ //prevent player from putting his king in danger
						RerollTurn(pieceInT1);
						gameEvents.pop();
					}
				}
				else if (DoEnPassant(pieceInT1, tile2Location))
				{
					gameEvents.push(DirectorEvent::TurnPassed);
					GenerateMovesForAllPieces();
					CheckKingsSafety();
					if (WillKingBeDead(pieceInT1))
					{ //prevent player from putting his king in danger
						RerollTurn(pieceInT1);
						gameEvents.pop();
					}
				}
			}

		}
		else //king is already under threat
		{
			if (pieceInT1 != nullptr && teamToPlay == pieceInT1->GetTeam())
			{
				if (MovePiece(pieceInT1,tile2Location)) //if moving succeed (if it actually moved!)
				{
					//do turn
					gameEvents.push(DirectorEvent::TurnPassed);					
					GenerateMovesForAllPieces();
					CheckKingsSafety();
					if (!AreKingsSafe())
					{ //prevent player from putting his king in danger
						RerollTurn(pieceInT1);
						gameEvents.pop();
					}
				}
				else if (DoCastling(pieceInT1, pieceInT2))
				{
					gameEvents.push(DirectorEvent::TurnPassed);
					GenerateMovesForAllPieces();
					CheckKingsSafety();
					if (!AreKingsSafe())
					{ //prevent player from putting his king in danger
						RerollTurn(pieceInT1);
						gameEvents.pop();
					}
				}
				else if (DoEnPassant(pieceInT1, tile2Location))
				{
					gameEvents.push(DirectorEvent::TurnPassed);
					GenerateMovesForAllPieces();
					CheckKingsSafety();
					if (WillKingBeDead(pieceInT1))
					{ //prevent player from putting his king in danger
						RerollTurn(pieceInT1);
						gameEvents.pop();
					}
				}
			}

		}
		DestroyMarkedPiece();
		CheckForEnPassants(gameTurn);
	}		
}

void GameDirector::HandleInputCheatMode(const Vec2I tile1Location, const Vec2I tile2Location, const GlobalEnums::Team teamToPlay, const int gameTurn)
{
	if (tile1Location != tile2Location) //if the 2 clicks locations are valid
	{
		//move the piece (if its logical)
		auto pieceInT1 = getPiece(tile1Location);
		auto pieceInT2 = getPiece(tile2Location);

		if (pieceInT1 != nullptr)
		{			
			if (DoCastling(pieceInT1, pieceInT2))
			{
				gameEvents.push(DirectorEvent::TurnPassed);
				GenerateMovesForAllPieces();
			}
			/*else if (DoEnPassant(pieceInT1, tile2Location))
			{
				gameEvents.push(DirectorEvent::TurnPassed);
				GenerateMovesForAllPieces();
			}*/
			 else if (PutPieceAt(pieceInT1, tile2Location)) //if moving succeed (if it actually moved!)
			{
				//do turn					
				gameEvents.push(DirectorEvent::TurnPassed);
				GenerateMovesForAllPieces();
			}
				CheckKingsSafety();
		}
		DestroyMarkedPiece();
		CheckForEnPassants(gameTurn);
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
				pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ location }, Team::BLACK, &board)));
				break;
			case GlobalEnums::ROOK:
				pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ location }, Team::BLACK, &board)));
				break;
			case GlobalEnums::BISHOP:
				pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ location }, Team::BLACK, &board)));
				break;
			case GlobalEnums::QUEEN:
				pieces.push_back(std::shared_ptr<Queen>(new Queen(Vec2I{ location }, Team::BLACK, &board)));
				break;
		}
	}
	else if (luckyPawn->GetTeam() == Team::WHITE)
	{
		switch (type)
		{
			case GlobalEnums::KNIGHT:
				pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ location }, Team::WHITE, &board)));
				break;
			case GlobalEnums::ROOK:
				pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ location }, Team::WHITE, &board)));
				break;
			case GlobalEnums::BISHOP:
				pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ location }, Team::WHITE, &board)));
				break;
			case GlobalEnums::QUEEN:
				pieces.push_back(std::shared_ptr<Queen>(new Queen(Vec2I{ location }, Team::WHITE, &board)));
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
				PutPieceAt(king, { king->Locate().x + 2,y });
				PutPieceAt(rook, { king->Locate().x - 1,y });
				return true;
			}
			else //rook is on left
			{
				PutPieceAt(king, { king->Locate().x - 2,y });
				PutPieceAt(rook, { king->Locate().x + 1,y });
				return true;
			}
		}
		else
			return false;
	}
	else
		return false;
}

bool GameDirector::DoEnPassant(std::shared_ptr<Piece> piece, Vec2I tileLoc)
{
	auto tile = board.GetTile(tileLoc);
	if (std::dynamic_pointer_cast<Pawn>(piece))
	{
		auto pawn = std::dynamic_pointer_cast<Pawn>(piece);
		if (std::find(pawn->getValidTiles().begin(), pawn->getValidTiles().end(), tile->location) != pawn->getValidTiles().end()) //if its valid tile
		{
			if (PutPieceAt(pawn,tile->location))
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

void GameDirector::CheckForEnPassants(int gameTurn)
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
	for (int x = 0; x < board.columns; x++)
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

	for (int x = 0; x < board.columns; x++)
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
				gameEvents.push(DirectorEvent(DirectorEvent::KingUnderThreat));
				return;
			}
			else if (*itr == WKingLoc)
			{
				WkingUnderThreat = true;
				threatningPiece = piece;
				gameEvents.push(DirectorEvent(DirectorEvent::KingUnderThreat));
				return;
			}
		}
		//if we reached this point, then there is none under threat
		WkingUnderThreat = false;
		BkingUnderThreat = false;
		threatningPiece = nullptr;
		gameEvents.push(DirectorEvent(DirectorEvent::KingIsSafe));
	}
}

void GameDirector::ReflectChangesToBoard(std::shared_ptr<Piece> piece)
{
	//affect all other pieces and tell board

	if (board.IsInsideTheBoard(piece->OldLocation()))
		board.ResetTile(piece->OldLocation());//supposing that we left this tile empty		

	auto tile = board.GetTile(piece->Locate());

	//if tile contains a piece then we send it to prison.
	if (tile->CurState().containPiece)
	{
		std::shared_ptr<Piece> p = getPiece(piece->Locate(), tile->CurState().piecetype, tile->CurState().pieceTeam);
		if (p != nullptr)
		{
			MarkForDestruction(p);
			//if captured piece is KING
			if (p->GetType() == KING)
				gameEvents.push(GameDirector::DirectorEvent::GameOver);
		}
	}

	// check for promotions
	if (dynamic_cast<Pawn*>(piece.get()) != nullptr && dynamic_cast<Pawn*>(piece.get())->isTransformed())
	{
		EnterPromotionMode(piece.get());

		//adding event
		if (piece->GetTeam() == Team::BLACK)
			gameEvents.push(GameDirector::DirectorEvent::EnterBlackPromotion);
		else if (piece->GetTeam() == Team::WHITE)
			gameEvents.push(GameDirector::DirectorEvent::EnterWhitePromotion);
	}

	// do changes to the tile which the piece moved TO
	board.PutPieceOnTile(piece->Locate(), piece);

	//report kings' location
	if (piece->GetType() == KING)
	{
		if (piece->GetTeam() == Team::BLACK)
			BKingLoc = piece->Locate();

		else if (piece->GetTeam() == Team::WHITE)
			WKingLoc = piece->Locate();
	}
}


//cheating functions 
