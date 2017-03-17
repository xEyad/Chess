#include "Board.h"
#include "Piece.h"
#include "Pawn.h"
#include <iostream>
#include "GameDirector.h"

const int Tile::HEIGHT = 80;
const int Tile::WIDTH = 80;
Board::Board(int rows, int columns, Surface* const sprite)
	:
	rows(rows),
	columns(columns),
	director(nullptr),
	sprite(sprite)
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
	for (unsigned int x = 0; x < sprite->GetWidth(); x++)
	{
		for (unsigned int y = 0; y < sprite->GetHeight(); y++)
		{
			sprSurf.push_back(sprite->GetPixel(x, y));
		}
	}

}

std::shared_ptr<Tile> Board::GetTile(Vec2I location) const
{
	for each (std::shared_ptr<Tile> t in boardTiles)
	{
		if (t->location == location)
			return t;
	}
	return nullptr;
}
std::shared_ptr<Tile> Board::GetTileByMouse(Vec2I mousePos) const
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
const Tile::Status Board::GetTileState(Vec2I location) const
{
	if (IsInsideTheBoard(location))
		return GetTile(location)->state;
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
		assert(!Tile->state.containPiece); //if it doesn't contain a piece then everything is OK
		//if your program crashed then thats what you did wrong:
		//initialized more than 1 piece on same spot/Location		
	}

	//do changes to the tile which the piece moved FROM
	else if (IsInsideTheBoard(oldLocation)) //basically not intialization
	{
		auto prevTile = GetTile(oldLocation);
		prevTile->applyChanges(false, pieceType::NOT_DEFINED, Team::INVALID); //supposing that we left this tile empty
	}

	//do changes to the tile which the piece moved TO
	auto tile = GetTile(piece->Locate());
	if (tile->state.containPiece)
	{
		//if this has moved then the new tile is either empty or have enemy piece.
		//if it contains a piece then we send it to prison.
		std::shared_ptr<Piece> p = director->getPiece(piece->Locate(), tile->state.piecetype, tile->state.pieceTeam);

		if (p != nullptr)
		{
			p->SendToPrison(); //should be deleted
		   //if captured piece is KING
			if (p->GetType() == KING)
				director->gameOver = true;
			director->DestroyPiece(p);
		}
	}
	if (dynamic_cast<Pawn*>(piece) != nullptr && dynamic_cast<Pawn*>(piece)->isTransformed())
	{
		piece = director->Transformed(piece).get();
	}
	tile->applyChanges(true, piece->GetType(), piece->GetTeam());

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
	//do changes to the tile which the piece moved FROM
	 if (IsInsideTheBoard(locationGoingTo)) 
	{
		auto tileUndoed = GetTile(locationGoingTo);
		tileUndoed->applyChanges(false, pieceType::NOT_DEFINED, Team::INVALID); 
	}

	//do changes to the tile which the piece moved BACK TO (Logically it should be empty already)
	auto tile = GetTile(curLocation);
	tile->applyChanges(true, piece->GetType(), piece->GetTeam());

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

void Board::DrawGrid( Graphics & gfx, Color edgesClr, Vec2I TopLeft)
{
	int xx = 0;
	int yy = 0;
	topLeft = TopLeft;
	Vec2I screenLocation = topLeft;
	for (auto i = boardTiles.cbegin(); i < boardTiles.cend(); i++)
	{
		//each tile location is topLeft corner of any Rect
		Vec2I startPoint(screenLocation.x + xx,screenLocation.y + yy);
		Vec2I endPoint(startPoint.x + Tile::WIDTH, startPoint.y + Tile::HEIGHT);
		gfx.DrawRect(RectI(startPoint, endPoint), edgesClr);
		xx += Tile::WIDTH;
		if ((*i)->location.x % (rows-1) == 0 && (*i)->location.x != 0) //first one = 0, if we pass the 7 then its new row
		{
			//go to the beginning and down a little bit
			xx = 0;
			yy += Tile::HEIGHT;
		}
	}
}

void Board::DrawGrid(Graphics & gfx, Color edgesClr) const
{
	int xx = 0;
	int yy = 0;
	Vec2I screenLocation = topLeft;
	for (auto i = boardTiles.cbegin(); i < boardTiles.cend(); i++)
	{
		//each tile location is topLeft corner of any Rect
		Vec2I startPoint(screenLocation.x + xx, screenLocation.y + yy);
		Vec2I endPoint(startPoint.x + Tile::WIDTH, startPoint.y + Tile::HEIGHT);
		gfx.DrawRect(RectI(startPoint, endPoint), edgesClr);
		xx += Tile::WIDTH;
		if ((*i)->location.x % (rows - 1) == 0 && (*i)->location.x != 0) //first one = 0, if we pass the 7 then its new row
		{
			//go to the beginning and down a little bit
			xx = 0;
			yy += Tile::HEIGHT;
		}
	}
}

void Board::DrawSprite(Graphics &gfx) const
{	
	auto i = sprSurf.begin();
	for (unsigned int x = 0; x < sprite->GetWidth(); x++)
	{
		for (unsigned int y = 0; y < sprite->GetHeight(); y++)
		{
			gfx.PutPixel(x, y, (*i++));
		}
	}

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
	Color c;
	Vec2I screenLocation = topLeft;
	for (auto i = director->pieces.cbegin(); i < director->pieces.cend(); i++)
	{
		if (IsInsideTheBoard((*i)->Locate()))
		{
			Vec2I topLeftPoint(screenLocation.x + (*i)->Locate().x * Tile::WIDTH  , screenLocation.y + (*i)->Locate().y * Tile::HEIGHT  );
			std::vector<Color> surf;

			for (unsigned int x = 0; x < (*i)->GetSprite()->GetWidth(); x++)
			{
				for (unsigned int y = 0; y < (*i)->GetSprite()->GetHeight(); y++)
				{
					surf.push_back((*i)->GetSprite()->GetPixel(x, y));
				}
			}

			auto ss = (*i)->GetSprSurf()->cbegin();
			
			for (unsigned int x = topLeftPoint.x; x < (*i)->GetSprite()->GetWidth() + topLeftPoint.x; x++)
			{
				for (unsigned int y = topLeftPoint.y; y < (*i)->GetSprite()->GetHeight() + topLeftPoint.y; y++)
				{
					if (!(ss->dword == 4294967295 ))//white
						gfx.PutPixelClipped(x, y, (*ss), RectI(0, Graphics::ScreenHeight, 0, Graphics::ScreenWidth));
					ss++;
				}
			}
		}
		else
			continue;
	}
}

void Board::DrawPieces(Graphics & gfx) const
{
	Color c;
	Vec2I screenLocation = topLeft;
	for (auto i = director->pieces.cbegin(); i < director->pieces.cend(); i++)
	{
		if (IsInsideTheBoard((*i)->Locate()))
		{
			//give it a color based on its type
			switch ((*i)->GetType())
			{
				case QUEEN:
					c = Colors::Red;
					break;
				case KING:
					c = Colors::Magenta;
					break;
				case BISHOP:
					c = Colors::Cyan;
					break;
				case ROOK:
					c = Colors::Yellow;
					break;
				case PAWN:
					c = Colors::Green;
					break;
				case KNIGHT:
					c = Colors::LightGray;
					break;
				default:
					c = Colors::Black;
					break;
			}
			Vec2I centerPoint(screenLocation.x + (*i)->Locate().x * Tile::WIDTH + (Tile::WIDTH / 2), screenLocation.y + (*i)->Locate().y * Tile::HEIGHT + (Tile::HEIGHT / 2));
			int size = Tile::WIDTH / 4;
			RectI r(centerPoint.y - size, centerPoint.y + size, centerPoint.x - size, centerPoint.x + size);
			gfx.DrawColoredRect(r, c);
		}
	}
}

