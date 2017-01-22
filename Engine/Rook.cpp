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

int Rook::howManyLeft() const
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

bool Rook::isValidLocation(Vec2I newLocation) const
{
	if (board->isInsideTheBoard(newLocation))
	{
		auto tile = board->getTileState(newLocation);
		if (!tile.containPiece || (tile.containPiece && tile.team != team)) //if it have no piece on it or have a piece of other team
		{
			if (curLocation.x == newLocation.x && curLocation.y != newLocation.y)
			{//moving only vertically
				if (isWayClear(newLocation))
					return true;
				else
					return false;
			}
			else if (curLocation.x != newLocation.x && curLocation.y == newLocation.y)
			{//moving only horizontally
				if (isWayClear(newLocation))
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

bool Rook::isWayClear(Vec2I newLocation) const
{
	int judge; //used to make us not check the tile we are currently on
	if (board->isInsideTheBoard(newLocation))
	{
		if (newLocation.x == curLocation.x) //then its a vertical move (Y)
		{
			for (int i = std::min(curLocation.y, newLocation.y); i < std::max(curLocation.y, newLocation.y) - 1; i++)
			{//start from the lowest to bigger. checks if any of those tiles have a piece on it
				if (Vec2I(curLocation.x, i) == curLocation)
					judge = 1;
				else
					judge = 0;
				if (board->getTileState(Vec2I(curLocation.x, i + judge)).containPiece)
					return false;
			}
			//if we get out of the loop then the way is clear
			return true;
		}
		else if (newLocation.y == curLocation.y) //then its a horizontal move (X)
		{
			for (int i = std::min(curLocation.x, newLocation.x); i < std::max(curLocation.x, newLocation.x) - 1; i++)
			{//start from the lowest to bigger. checks if any of those tiles have a piece on it
				if (Vec2I(i, curLocation.y) == curLocation)
					judge = 1;
				else
					judge = 0;
				if (board->getTileState(Vec2I(i + 1, curLocation.y)).containPiece) //we dont check the last point
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

void Rook::moveTo(Vec2I newLocation)
{
	if (isValidLocation(newLocation))
	{
		oldLocation = curLocation;
		curLocation = newLocation;
		movedBefore = true;	
		reportChange();
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
int Rook::nWhiteLeft = 0;
int Rook::nBlackLeft = 0;