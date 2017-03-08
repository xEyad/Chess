#include "King.h"

King::King(Vec2I location, Team team, Board* const board, Surface* const sprite)
	:
	Piece(location, team, KING, board,sprite)
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
bool King::IsValidLocation(int newLocation) const
{
	return IsValidLocation(TransLocation(newLocation));
}
bool King::IsWayClear(Vec2I newLocation) const
{
	return false;
}
bool King::IsWayClear(int newLocation) const
{
	return IsWayClear(TransLocation(newLocation));
}
bool King::MoveTo(Vec2I newLocation)
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
bool King::MoveTo(int newLocation)
{
	return MoveTo(TransLocation(newLocation));
}

void King::GenerateValidMoves()
{
	validTiles.clear();
	for (int y = curLocation.y - 1; y <= curLocation.y + 1; y++)
	{
		for (int x = curLocation.x - 1; x <= curLocation.x + 1; x++)
		{
			if (IsValidLocation({ x,y }))
				validTiles.push_back({ x,y });
		}
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

