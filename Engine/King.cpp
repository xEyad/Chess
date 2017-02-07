#include "King.h"

King::King(Vec2I location, Team team, Board* const board)
	:
	Piece(location, team, KING, board)
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


int King::howManyLeft() const
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
bool King::isValidLocation(Vec2I newLocation) const
{
	if (board->isInsideTheBoard(newLocation))
	{
		int xDiff = abs(newLocation.x - curLocation.x);
		int yDiff = abs(newLocation.y - curLocation.y);
		if (xDiff <= 1 && yDiff <= 1 && board->getTileState(newLocation).pieceTeam != team)
			return true;
		else
			return false;
	}
	else
		return false;
}
bool King::isWayClear(Vec2I newLocation) const
{
	return false;
}

void King::moveTo(Vec2I newLocation)
{
	if (isValidLocation(newLocation))
	{
		oldLocation = curLocation;
		curLocation = newLocation;
		movedBefore = true;
		reportChange();
	}
}

King::~King()
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
int King::nWhiteLeft = 0;
int King::nBlackLeft = 0;

bool King::isValidLocation(int newLocation) const
{
	return isValidLocation(TransLocation(newLocation));
}
bool King::isWayClear(int newLocation) const
{
	return isWayClear(TransLocation(newLocation));
}
void King::moveTo(int newLocation)
{
	moveTo(TransLocation(newLocation));
}