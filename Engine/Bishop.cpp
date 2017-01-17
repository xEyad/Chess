#include "Bishop.h"

Bishop::Bishop(Vec2I location, Team team, Board *const board)
	:
	Piece(location, team, BISHOP, board)
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

int Bishop::howManyLeft() const
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

bool Bishop::isValidLocation(Vec2I newLocation) const
{
	if (board->isInsideTheBoard(newLocation))
	{
		if (curLocation.x == newLocation.x || curLocation.y == newLocation.y) //if same Y or X
			return false;
		else
		{
			int xDiff = abs(curLocation.x - newLocation.x);
			int yDiff = abs(curLocation.y - newLocation.y);
			if (xDiff == 1 && yDiff == 1) //diagonalic move
			{
				if (isWayClear(newLocation) && board->getTileState(newLocation).team != team) //if the way is clear and there is no friend on it(new tile)
					return true;
				else 
					return false;
			}
		}
	}
	else //out of board
		return false;
}

bool Bishop::isWayClear(Vec2I newLocation) const
{		
		int yStart = std::min(curLocation.y, newLocation.y) + 1;
		int yEnd = std::max(curLocation.y, newLocation.y) - 1;
		//we start at the lowest Y
		if (newLocation.x > curLocation.x) //going right
		{
			if (newLocation.y > curLocation.y) //going right down
			{
				// start from current location then x increase to the newLocation
				int x = curLocation.x + 1;
				for (int y = yStart; y < yEnd; y++)
				{//start from the lowest to bigger. checks if any of those tiles have a piece on it dont check the last or the current
					if (board->getTileState(Vec2I(x, y)).containPiece)
						return false;
					x++;
				}
				//if we get out of the loop then the way is clear
				return true;
			}
			else //going right up
			{
				// start from newlocation then x decrease to the current piece location
				int x = newLocation.x + 1;
				for (int y = yStart; y < yEnd; y++)
				{//start from the lowest to bigger. checks if any of those tiles have a piece on it dont check the last or the current
					if (board->getTileState(Vec2I(x, y)).containPiece)
						return false;
					x--;
				}
				//if we get out of the loop then the way is clear
				return true;
			}
		}
		else //going left
		{
			if (newLocation.y > curLocation.y) //going down left
			{
				// start from current location then x decrease to the newLocation
				int x = curLocation.x + 1;
				for (int y = yStart; y < yEnd; y++)
				{//start from the lowest to bigger. checks if any of those tiles have a piece on it dont check the last or the current
					if (board->getTileState(Vec2I(x, y)).containPiece)
						return false;
					x--;
				}
				//if we get out of the loop then the way is clear
				return true;
			}
			else //going up left
			{
				// start from newlocation then x increase to the current piece location
				int x = newLocation.x + 1;
				for (int y = yStart; y < yEnd; y++)
				{//start from the lowest to bigger. checks if any of those tiles have a piece on it dont check the last or the current
					if (board->getTileState(Vec2I(x, y)).containPiece)
						return false;
					x++;
				}
				//if we get out of the loop then the way is clear
				return true;
			}
		}
}


void Bishop::moveTo(Vec2I newLocation)
{
	if (isValidLocation(newLocation))
	{
		oldLocation = curLocation;
		curLocation = newLocation;
	}
}

Bishop::~Bishop()
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

int Bishop::nWhiteLeft = 0;
int Bishop::nBlackLeft = 0;