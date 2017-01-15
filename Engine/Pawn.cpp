#include "Pawn.h"
Pawn::Pawn(Vec2I location, Team team, const Board *board)
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
	///return the number of pieces left in this team
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
	//checking if the location is inside the board
	if (newLocation.y <= board->rows &&
		newLocation.x <= board->columns &&
		newLocation.y >= 0 &&
		newLocation.x >= 0
		)
	{
		switch (team)
		{
			case Team::WHITE:
			{//eating case is missing
				if (newLocation.x == location.x)
				{
					if (movedBefore == false)
					{
						if (newLocation.y == location.y - 2 || newLocation.y == location.y - 1)
						{//if it is a move of 1 or 2 points
							return true;
						}
						else
						{
							return false;
						}
					}
					else
					{
						if (newLocation.y == location.y - 1)
						{//only on tile is allowed
							return true;
						}
						else
						{
							return false;
						}
					}
				}
				else
					return false;
			}

			case Team::BLACK:
			{
				{//eating case is missing
					if (newLocation.x == location.x)
					{
						if (movedBefore == false)
						{
							if (newLocation.y == location.y + 2 || newLocation.y == location.y + 1)
							{//if it is a move of 1 or 2 points

								return true;
							}
							else
							{
								return false;
							}
						}
						else
						{
							if (newLocation.y == location.y + 1)
							{//only on tile is allowed
								return true;
							}
							else
							{
								return false;
							}
						}
					}
					else
						return false;
				}
			}

			case Team::INVALID:
				return false;
		}
	}
	else
		return false;
}

void Pawn::moveTo(Vec2I newLocation)
{
	if (isValidLocation(newLocation))
	{
		location = newLocation;
		movedBefore = true;
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