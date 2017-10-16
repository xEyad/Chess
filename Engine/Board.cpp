#include "Board.h"
#include "Piece.h"

const int Board::Tile::HEIGHT = 80;
const int Board::Tile::WIDTH = 80;
Board::Board(int rows, int columns)
	:
	rows(rows),
	columns(columns)
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

Board::Board(Board& board)
	:
	rows(board.rows),
	columns(board.columns)
{	
	boardTiles = board.boardTiles;
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
std::shared_ptr<Board::Tile> Board::GetTileByMouse(Vec2I gridTopLeft, Vec2I mousePos) const
{
	//check if its inside any tile
	int xx = 0;
	int yy = 0;
	Vec2I screenLocation = gridTopLeft;
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

bool Board::IsInsideTheBoard(Vec2I location) const
{
	if (location.y < rows && location.x < columns && location.y >= 0 && location.x >= 0)		
		return true;
	else
		return false;
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

void Board::PutPieceOnTile(Vec2I TileLocation, std::shared_ptr<Piece> piece)
{
	GetTile(TileLocation).get()->ApplyChanges(true, piece->GetType(), piece->GetTeam());
}
