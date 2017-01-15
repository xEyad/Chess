#include "Rook.h"



Rook::Rook(Vec2I location, Team team, const Board* const board)
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
	auto tile = board->getTileState(newLocation);
	if (!tile.containPiece || (tile.containPiece && tile.team != team)) //if it have no piece on it or have a piece of other team
	{
		if (location.x == newLocation.x && location.y != newLocation.y)
		{//moving only vertically
			return true;
		}
		else if (location.x != newLocation.x && location.y == newLocation.y)
		{//moving only horizontally
			return true;
		}
		else
		{
			return false;
		}
	}
	else //the tile contain a piece of the same team
		return false;
}

void Rook::moveTo(Vec2I newLocation)
{
	if (isValidLocation(newLocation))
	{
		location = newLocation;
		movedBefore = true;
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