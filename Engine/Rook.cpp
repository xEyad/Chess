#include "Rook.h"

Rook::Rook(Vec2I location, Team team, Board* const board)
	:
	Piece(location, team, ROOK, board)
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
		if (!tile.containPiece || (tile.containPiece && tile.pieceTeam != team)) //if it have no piece on it or have a piece of other team
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
	int judge; //used to make us not check the tile we are currently on
	if (board->IsInsideTheBoard(newLocation))
	{
		if (newLocation.x == curLocation.x) //then its a vertical move (Y)
		{
			for (int i = min(curLocation.y, newLocation.y); i < max(curLocation.y, newLocation.y) - 1; i++)
			{//start from the lowest to bigger. checks if any of those tiles have a piece on it
				if (Vec2I(curLocation.x, i) == curLocation)
					judge = 1;
				else
					judge = 0;
				if (board->GetTileState(Vec2I(curLocation.x, i + judge)).containPiece)
					return false;
			}
			//if we get out of the loop then the way is clear
			return true;
		}
		else if (newLocation.y == curLocation.y) //then its a horizontal move (X)
		{
			for (int i = min(curLocation.x, newLocation.x); i < max(curLocation.x, newLocation.x) - 1; i++)
			{//start from the lowest to bigger. checks if any of those tiles have a piece on it
				if (Vec2I(i, curLocation.y) == curLocation)
					judge = 1;
				else
					judge = 0;
				if (board->GetTileState(Vec2I(i + 1, curLocation.y)).containPiece) //we dont check the last point
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

bool Rook::MoveTo(Vec2I newLocation)
{
	if (IsValidLocation(newLocation))
	{
		oldLocation = curLocation;
		curLocation = newLocation;
		movedBefore = true;
		ReportChange();
		return true;
	}
	else
		return false;
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
int Rook::nWhiteLeft = 0;
int Rook::nBlackLeft = 0;

bool Rook::IsValidLocation(int newLocation) const
{
	return IsValidLocation(TransLocation(newLocation));
}
bool Rook::IsWayClear(int newLocation) const
{
	return IsWayClear(TransLocation(newLocation));
}
bool Rook::MoveTo(int newLocation)
{
	return MoveTo(TransLocation(newLocation));
}