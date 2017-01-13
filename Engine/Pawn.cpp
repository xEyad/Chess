#include "Pawn.h"
Pawn::Pawn(Vec2I location, Team team, const Board *board)
	:
	Piece(location, team, PAWN, board)
{
	switch (team)
	{
		case Piece::Team::WHITE:
			nWhiteLeft++;
			break;
		case Piece::Team::BLACK:
			nBlackLeft++;
			break;
	}
}


int Pawn::howManyLeft() const
{
	///return the number of pieces left in this team
	switch (team)
	{
		case Piece::Team::WHITE:
			return nWhiteLeft;
			break;
		case Piece::Team::BLACK:
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
	if (newLocation.x <= board->rows &&
		newLocation.y <= board->columns &&
		newLocation.x >= 0 &&
		newLocation.y >= 0
		)
	{
		switch (team)
		{
			case Piece::Team::WHITE:
			{//eating case is missing
				if (newLocation.y == location.y)
				{
					if (movedBefore == false)
					{
						if (newLocation.x == location.x - 2 || newLocation.x == location.x - 1)
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
						if (newLocation.x == location.x - 1)
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

			case Piece::Team::BLACK:
			{
				{//eating case is missing
					if (newLocation.y == location.y)
					{
						if (movedBefore == false)
						{
							if (newLocation.x == location.x + 2 || newLocation.x == location.x + 1)
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
							if (newLocation.x == location.x + 1)
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

			case Piece::Team::INVALID:
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
		case Piece::Team::WHITE:
			nWhiteLeft--;
			break;
		case Piece::Team::BLACK:
			nBlackLeft--;
			break;
	}
}

//static variables should be intialized like this, in the def file!
int Pawn::nWhiteLeft = 0;
int Pawn::nBlackLeft = 0;