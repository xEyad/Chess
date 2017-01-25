#include "Pawn.h"
Pawn::Pawn(Vec2I location, Team team,  Board *const board)
	:
	Piece(location, team, PAWN, board)
{
	//increment n of pieces
	switch (team)
	{
		case Team::WHITE:
			nWhiteLeft++;
			break;
		case Team::BLACK:
			nBlackLeft++;
			break;
	}
}


int Pawn::howManyLeft() const
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

bool Pawn::isValidLocation(Vec2I newLocation) const
{
	if (team == Team::BLACK && curLocation.y > newLocation.y)		//black and tries to move up
		return false;

	else if (team == Team::WHITE && curLocation.y < newLocation.y)	//white and tries to move down
		return false;
	else 													//other than that... then its a valid move
	{
		auto tile = board->getTileState(newLocation);
		int yDiff = abs(curLocation.y - newLocation.y);
		int xDiff = abs(curLocation.x - newLocation.x);
		if (!movedBefore && isWayClear(newLocation) && yDiff <= 2)	// can do 2 vertical moves 
			return true;

		else if (isWayClear(newLocation) && yDiff == 1) //basically 1 vertical move
			return true;

		else if (yDiff == 1 && xDiff == 1 && tile.team != team) //eating(capturing) case
		{
			return true;
		}
		else
			return false;
	}
	
}

bool Pawn::isWayClear(Vec2I newLocation) const
{
	if (board->isInsideTheBoard(newLocation) && newLocation.x == curLocation.x)
	{
		int judge;
		for (int i = min(curLocation.y, newLocation.y); i < max(curLocation.y, newLocation.y)-1; i++)
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
	else
		return false;
}

void Pawn::moveTo(Vec2I newLocation)
{
	if (isValidLocation(newLocation))
	{
		oldLocation = curLocation;
		curLocation = newLocation;
		movedBefore = true;
		reportChange();
	}
}

Pawn::~Pawn()
{
	
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

//static variables should be intialized like this, in the def file!
int Pawn::nWhiteLeft = 0;
int Pawn::nBlackLeft = 0;