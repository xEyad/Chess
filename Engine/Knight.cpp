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

int Knight::HowManyLeft() const
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

bool Knight::IsValidLocation(Vec2I newLocation) const
{
	if (board->IsInsideTheBoard(newLocation))
	{
		bool notFriendly = board->GetTileState(newLocation).pieceTeam != team;
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

bool Knight::IsWayClear(Vec2I newLocation) const
{
		return false;
}


bool Knight::MoveTo(Vec2I newLocation)
{
	if (IsValidLocation(newLocation))
	{
		oldLocation = curLocation;
		curLocation = newLocation;
		ReportChange();
		return true;
	}
	else
		return false;
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

bool Knight::IsValidLocation(int newLocation) const
{
	return IsValidLocation(TransLocation(newLocation));
}
bool Knight::IsWayClear(int newLocation) const
{
	return IsWayClear(TransLocation(newLocation));
}
bool Knight::MoveTo(int newLocation)
{
	return MoveTo(TransLocation(newLocation));
}
