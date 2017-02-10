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


int King::HowManyLeft() const
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
bool King::IsValidLocation(Vec2I newLocation) const
{
	if (board->IsInsideTheBoard(newLocation))
	{
		int xDiff = abs(newLocation.x - curLocation.x);
		int yDiff = abs(newLocation.y - curLocation.y);
		if (xDiff <= 1 && yDiff <= 1 && board->GetTileState(newLocation).pieceTeam != team)
			return true;
		else
			return false;
	}
	else
		return false;
}
bool King::IsWayClear(Vec2I newLocation) const
{
	return false;
}

void King::MoveTo(Vec2I newLocation)
{
	if (IsValidLocation(newLocation))
	{
		oldLocation = curLocation;
		curLocation = newLocation;
		movedBefore = true;
		ReportChange();
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

bool King::IsValidLocation(int newLocation) const
{
	return IsValidLocation(TransLocation(newLocation));
}
bool King::IsWayClear(int newLocation) const
{
	return IsWayClear(TransLocation(newLocation));
}
void King::MoveTo(int newLocation)
{
	MoveTo(TransLocation(newLocation));
}