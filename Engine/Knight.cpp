#include "Knight.h"



Knight::Knight(Vec2I location, Team team, Board* const board)
	:
Piece(location, team, KNIGHT, board)
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

int Knight::howManyLeft() const
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

bool Knight::isValidLocation(Vec2I newLocation) const
{
	if (board->isInsideTheBoard(newLocation))
	{
		bool notFriendly = board->getTileState(newLocation).team != team;
		int xDiff = abs(newLocation.x - curLocation.x);
		int yDiff = abs(newLocation.y - curLocation.y);

		if (xDiff == 1 && yDiff == 2 && notFriendly)
			return true;
		else if (xDiff == 2 && yDiff == 1 && notFriendly)
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Knight::isWayClear(Vec2I newLocation) const
{
		return false;
}


void Knight::moveTo(Vec2I newLocation)
{
	if (isValidLocation(newLocation))
	{
		oldLocation = curLocation;
		curLocation = newLocation;
		reportChange();
	}
}

Knight::~Knight()
{//decrement number of pieces
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
int Knight::nWhiteLeft = 0;
int Knight::nBlackLeft = 0;


