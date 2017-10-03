#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include <iostream>
#include "GameDirector.h"

#include "BoardPainter.h"
#include "PiecesPainter.h"
const int Board::Tile::HEIGHT = 80;
const int Board::Tile::WIDTH = 80;
Board::Board(int rows, int columns)
	:
	rows(rows),
	columns(columns),
	director(nullptr)
{
	//i should give tiles names (a2,b5) ... but thats for later

	Color c[] = { Colors::Black, Colors::White };
	int i = 1; //first tile is white
	for (int row = 0; row < rows; row++)
	{
		for (int col = 0; col < columns; col++)
		{
			//Rows are Y , Columns are X
			boardTiles.push_back( std::shared_ptr<Tile> (new Tile(Vec2I(col,row),c[i])));
			i++;
			if (i > 1) //so that i goes 0-1 to alternate between white and black
				i = 0;
		}
		i++;
		if (i > 1) //so that i goes 0-1 to alternate between white and black
			i = 0;
	}

}

Board::Board(Board&& board)
	:
	rows(board.rows),
	columns(board.columns),
	director(board.director),
	boardTiles(std::move(board.boardTiles))
{	}

int Board::GetTileWidth() 
{
	return Tile::WIDTH;
}

int Board::GetTileHeight() 
{
	return Tile::HEIGHT;
}

std::shared_ptr<Board::Tile> Board::GetTile(Vec2I location) const
{
	for each (std::shared_ptr<Tile> t in boardTiles)
	{
		if (t->location == location)
			return t;
	}
	return nullptr;
}
std::shared_ptr<Board::Tile> Board::GetTileByMouse(Vec2I mousePos) const
{
	//check if its inside any tile
	int xx = 0;
	int yy = 0;
	Vec2I screenLocation = topLeft;
	for (auto i = boardTiles.cbegin(); i < boardTiles.cend(); i++)
	{
		//each tile location is topLeft corner of any Rect
		Vec2I startPoint(screenLocation.x + xx, screenLocation.y + yy);
		Vec2I endPoint(startPoint.x + Tile::WIDTH, startPoint.y + Tile::HEIGHT);
		xx += Tile::WIDTH;

		//if mouse is inside this rectangle (tile)
		if (mousePos.x > startPoint.x && mousePos.x < endPoint.x && mousePos.y > startPoint.y && mousePos.y < endPoint.y)
			return *i;

		if ((*i)->location.x % (8 - 1) == 0 && (*i)->location.x != 0) //first one = 0, if we pass the 7 then its new row
		{
			//go to the beginning and down a little bit
			xx = 0;
			yy += Tile::HEIGHT;
		}
	}
	return nullptr;
}
const Board::Tile::Status Board::GetTileState(Vec2I location) const
{
	if (IsInsideTheBoard(location))
		return GetTile(location)->curState;
	else
	{
		Tile::Status s;
		s.containPiece = false;
		s.piecetype = pieceType::NOT_DEFINED;
		s.pieceTeam = Team::INVALID;
		return s;
	}
}
//graphical start point (in screen coordinates)
Vec2I Board::GetTileStartPoint(Vec2I Tilelocation) const
{
	return Vec2I(topLeft.x + Tilelocation.x * Tile::WIDTH, topLeft.y + Tilelocation.y * Tile::HEIGHT);
}

bool Board::IsInsideTheBoard(Vec2I location) const
{
	if (location.y < rows && location.x < columns && location.y >= 0 && location.x >= 0)		
		return true;
	else
		return false;
}

void Board::ReadChange(Piece * piece, Vec2I oldLocation)
{//board checks the piece for new changes and adapt itself to it

	//intialization case (can't add two pieces in the same location)
	if (!IsInsideTheBoard(oldLocation))
	{
		auto Tile = GetTile(piece->Locate());
		//assert(!Tile->curState.containPiece); //if it doesn't contain a piece then everything is OK
		//if your program crashed then thats what you did wrong:
		//initialized more than 1 piece on same spot/Location		
	}

	//do changes to the tile which the piece moved FROM
	else if (IsInsideTheBoard(oldLocation)) //basically not intialization
	{
		auto prevTile = GetTile(oldLocation);
		prevTile->ApplyChanges(false, pieceType::NOT_DEFINED, Team::INVALID); //supposing that we left this tile empty
	}

	//do changes to the tile which the piece moved TO
	auto tile = GetTile(piece->Locate());
	if (tile->curState.containPiece)
	{
		//if this has moved then the new tile is either empty or have enemy piece.
		//if it contains a piece then we send it to prison.
		std::shared_ptr<Piece> p = director->getPiece(piece->Locate(), tile->curState.piecetype, tile->curState.pieceTeam);

		if (p != nullptr)
		{
			p->SendToPrison(); //should be deleted

		   //if captured piece is KING
			if (p->GetType() == KING)
			{
				director->gameOver = true;
				director->gameEvents.push(GameDirector::DirectorEvent::GameOver);
			}
			director->MarkForDestruction(p);
		}
	}
	// check for promotions
	if (dynamic_cast<Pawn*>(piece) != nullptr && dynamic_cast<Pawn*>(piece)->isTransformed())
	{
		director->EnterPromotionMode(piece);

		//adding event
		if (piece->GetTeam() == Team::BLACK)
			director->gameEvents.push(GameDirector::DirectorEvent::EnterBlackPromotion);
		else if (piece->GetTeam() == Team::WHITE)
			director->gameEvents.push(GameDirector::DirectorEvent::EnterWhitePromotion);
	}
	tile->ApplyChanges(true, piece->GetType(), piece->GetTeam());

	//report kings' location
	if (piece->GetType() == KING)
	{
		if (director)//not intialization
		{
			if (piece->GetTeam() == Team::BLACK)
				director->BKingLoc = piece->Locate();

			else if (piece->GetTeam() == Team::WHITE)
				director->WKingLoc = piece->Locate();
		}		
	}
}
void Board::ReadChange(Piece * piece, Vec2I locationGoingTo, bool Undo)
{
	auto curLocation = piece->LastTurn().curLocation; //location the pieace CAME BACK TO
	director->RemoveDestructionMark();
	//do changes to the tile which the piece moved FROM
	if (IsInsideTheBoard(locationGoingTo)) 
	{
		auto tileToUndo = GetTile(locationGoingTo);
		tileToUndo->UndoChanges();
	}

	//do changes to the tile which the piece moved BACK TO (Logically it should be empty already)
	auto tile = GetTile(curLocation);
	tile->UndoChanges();

	//report kings' location
	if (piece->GetType() == KING)
	{
		if (director)//not intialization
		{
			if (piece->GetTeam() == Team::BLACK)
				director->BKingLoc = curLocation;

			else if (piece->GetTeam() == Team::WHITE)
				director->WKingLoc = curLocation;
		}

	}
}

void Board::ResetAllTiles()
{
	for each (auto tile in boardTiles)
	{
		tile->Reset();
	}
}

void Board::ResetTile(Vec2I TileLocation)
{
	GetTile(TileLocation)->Reset();
}

void Board::DrawGrid( Graphics & gfx, Color edgesClr, Vec2I TopLeft)
{
	static BoardPainter painter(gfx);
	painter.DrawGrid(*this, TopLeft, edgesClr);
}

void Board::DrawGrid(Graphics & gfx, Color edgesClr) const
{
	static BoardPainter painter(gfx);
	painter.DrawGrid(*this, topLeft, edgesClr);	
}

void Board::DrawLabels(Graphics & gfx, Color labelsClr) const
{
	TextSurface::Font fonto(L"times", 15.0f);

	for (int cols = 0; cols < 8; cols++)
	{
		Vec2I start(topLeft.x+35,topLeft.y);
		int offSetX = Tile::WIDTH;
		int offSetY = -21;

		Vec2I topRowLabels(start.x + offSetX*cols, start.y + offSetY); 
		Vec2I botRowLabels(topRowLabels.x, start.y - offSetY * 4 - 7 + topRowLabels.y + Tile::HEIGHT * (columns -1));

		gfx.DrawText(std::to_wstring(cols), topRowLabels, fonto, labelsClr);
		gfx.DrawText(std::to_wstring(cols), botRowLabels, fonto, labelsClr);
	}
	for (int rows = 0; rows < 8; rows++)
	{
		Vec2I start(topLeft.x , topLeft.y + 35);
		int offSetX = -20;
		int offSetY = Tile::HEIGHT;

		Vec2I topRowLabels(start.x + offSetX, start.y + offSetY*rows); 
		Vec2I botRowLabels(topRowLabels.x + Tile::WIDTH * (this->rows - 1) - offSetX * 5 + 3, topRowLabels.y);

		gfx.DrawText(std::to_wstring(rows), topRowLabels, fonto, labelsClr);
		gfx.DrawText(std::to_wstring(rows), botRowLabels, fonto, labelsClr);
	}
}


void Board::DrawSprite(Graphics &gfx) const
{	
	static BoardPainter painter(gfx);
	painter.DrawSprite(2);
}

void Board::HighlightTile(Graphics & gfx, Vec2I mousePos, Color edgesClr) const
{
	// check if its inside any tile
	for (auto itr = boardTiles.cbegin(); itr < boardTiles.cend(); itr++)
	{
		//each tile location is topLeft corner of any Rect
		Vec2I startPoint(GetTileStartPoint((*itr)->location));
		Vec2I endPoint(startPoint.x + Tile::WIDTH, startPoint.y + Tile::HEIGHT);

		//if mouse is inside this rectangle (tile)
		if (mousePos.x > startPoint.x && mousePos.x < endPoint.x && mousePos.y > startPoint.y && mousePos.y < endPoint.y)
			gfx.DrawColoredRect(RectI(startPoint, endPoint), edgesClr, 72, false); //change value to 80+ if you don't want the small square 

		
	}
}

void Board::HighlightTiles(Graphics & gfx, std::vector<Vec2I> tilesPos, Color edgesClr) const
{
	for (auto i = tilesPos.cbegin(); i < tilesPos.cend(); i++)
	{
		//each tile location is topLeft corner of any Rect
		Vec2I startPoint(GetTileStartPoint(*i));
		Vec2I endPoint(startPoint.x + Tile::WIDTH, startPoint.y + Tile::HEIGHT);
		Vec2I centerPoint(startPoint.x + (Tile::WIDTH / 2), startPoint.y + (Tile::HEIGHT / 2));
		int size = Tile::WIDTH / 9;
		RectI r(centerPoint.y - size, centerPoint.y + size, centerPoint.x - size, centerPoint.x + size);
		//gfx.DrawColoredRect(RectI(startPoint, endPoint), edgesClr, 72, false); //change value to 80+ if you don't want the small square 
		//gfx.DrawColoredRect(RectI(startPoint, endPoint), edgesClr, -72, true); //change value to 80+ if you don't want the small square 
		gfx.DrawColoredRect(r, edgesClr);
	}
}

void Board::DrawPiecesSprite( Graphics & gfx) const
{
	static PiecesPainter pp(gfx, director->getPieces());
	pp.DrawPiecesSprites(topLeft,1);	
}
void Board::DrawPieces(Graphics & gfx) const
{
	static PiecesPainter pp(gfx, director->getPieces());
	pp.DrawPiecesSquares(topLeft);
}

