#include "Rook.h"
Rook::Rook(Vec2I location, Team team, Board* const board, Surface* const sprite)
	:
	Piece(location, team, ROOK, board,sprite)
{
	//increment number of pieces
	switch (team)
	{
		case Team::WHITE:
			nWhiteLeft++;
			break;
		case Team::BLACK:
			nBlackLeft++;
			break;
	}
};

int Rook::HowManyLeft() const
{
	switch (team)
	{
		case Team::WHITE:
			return nWhiteLeft;
			break;
		case Team::BLACK:
			return nBlackLeft;
			break;
		default:
			return -1;
			break;
	}
}

bool Rook::IsValidLocation(Vec2I newLocation) const
{
	if (board->IsInsideTheBoard(newLocation))
	{
		auto tile = board->GetTileState(newLocation);
		if (!tile.containPiece || (tile.containPiece && tile.pieceTeam == enemyTeam)) //if it have no piece on it or have a piece of other team
		{
			if (curLocation.x == newLocation.x && curLocation.y != newLocation.y)
			{//moving only vertically
				if (IsWayClear(newLocation))
					return true;
				else
					return false;
			}
			else if (curLocation.x != newLocation.x && curLocation.y == newLocation.y)
			{//moving only horizontally
				if (IsWayClear(newLocation))
					return true;
				else
					return false;
			}
			else
			{
				return false;
			}
		}
		else //the tile contain a piece of the same team
			return false;
	}
	else //newLocation is out of board range
		return false;
}

bool Rook::IsWayClear(Vec2I newLocation) const
{
	if (board->IsInsideTheBoard(newLocation))
	{		
		if (newLocation.x == curLocation.x) //then its a vertical move (Y)
		{
			
			for (int y = min(curLocation.y, newLocation.y) + 1; y < max(curLocation.y, newLocation.y) ; y++)
			{//start from the lowest to bigger. checks if any of those tiles have a piece on it
				if (board->GetTileState(Vec2I(curLocation.x, y)).containPiece)
					return false;
			}
			//if we get out of the loop then the way is clear
			return true;
		}
		else if (newLocation.y == curLocation.y) //then its a horizontal move (X)
		{
			for (int x = min(curLocation.x, newLocation.x) + 1; x < max(curLocation.x, newLocation.x) ; x++)
			{//start from the lowest to bigger. checks if any of those tiles have a piece on it
				if (board->GetTileState(Vec2I(x, curLocation.y)).containPiece) //we dont check the last point
					return false;
			}
			//if we get out of the loop then the way is clear
			return true;
		}
		else
			return false;
	}
	else
		return false;
} 



void Rook::GenerateValidMoves()
{
	if (captured)
		return;
	validTiles.clear();
	for (auto x = 0; x < board->rows; x++)
	{
		if (IsValidLocation({ x,curLocation.y }))
			validTiles.push_back({ x,curLocation.y });
	}
	for (auto y = 0; y < board->columns; y++)
	{
		if (IsValidLocation({ curLocation.x,y }))
			validTiles.push_back({ curLocation.x,y });
	}
}

Rook::~Rook()
{
	//decrement number of pieces
	switch (team)
	{
		case Team::WHITE:
			nWhiteLeft--;
			break;
		case Team::BLACK:
			nBlackLeft--;
			break;
	}
}

bool Rook::IsValidLocation(int newLocation) const
{
	return IsValidLocation(TransLocation(newLocation));
}
bool Rook::IsWayClear(int newLocation) const
{
	return IsWayClear(TransLocation(newLocation));
}



int Rook::nWhiteLeft = 0;
int Rook::nBlackLeft = 0;