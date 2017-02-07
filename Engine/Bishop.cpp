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
			if (xDiff == 1 && yDiff == 1 && board->getTileState(newLocation).pieceTeam != team) //diagonalic ONE move just ONE
			{
				return true;
			}
			else if (isWayClear(newLocation) && board->getTileState(newLocation).pieceTeam != team) //if the way is clear and there is no friend on it(new tile)
				return true;
			else
				return false;
		}
	}
	else //out of board
		return false;
}
bool Bishop::isValidLocation(int newLocation) const
{
	return isValidLocation(TransLocation(newLocation));
}

bool Bishop::isWayClear(Vec2I newLocation) const
{
	//checks for diagonalic move(s)
	int yStart = min(curLocation.y, newLocation.y) + 1; //we start at the lowest Y
	int yEnd = max(curLocation.y, newLocation.y); //is the place of the other piece
	int lastY = yStart-1;
	int lastX;
	bool enteredLoop = false; //we may not even enter the loop!
	
	if (newLocation.x > curLocation.x) //going right
	{
		if (newLocation.y > curLocation.y) //going right down
		{
			// start from current location then x increase to the newLocation		
			int x = curLocation.x + 1;
			lastX = curLocation.x;

			//first we check its diagonal move
			for (int y = yStart, tempX = x; y <= yEnd; y++, tempX++)
			{
				if (y == yEnd) //at last point (after moving diagonally)
					if (newLocation != Vec2I(tempX, y))  //if the last point isn't the newLocation then thats mean its not a diagonalic move
						return false;
			}

			//then we do check the path itself for any obstacles
			for (int y = yStart; y < yEnd; y++, x++)
			{//checks if the in-between tiles have a piece on it
				enteredLoop = true;
				if (board->getTileState(Vec2I(x, y)).containPiece)
					return false;
				 lastX = x;
				 lastY = y;			
			}
			if (enteredLoop)//if we get out of the loop, then everything is good
				return true;
			else
				return false;
		}
		else //going right up
		{
			// start from newlocation then x decrease to the current piece location
			int x = newLocation.x - 1;
			lastX = newLocation.x;

			//first we check its diagonal move
			for (int y = yStart, tempX = x; y <= yEnd; y++, tempX--)
			{
				if (y == yEnd) //at last point (after moving diagonally)
					if (curLocation != Vec2I(tempX, y))  //if the last point isn't the curLocation then thats mean its not a diagonalic move
						return false;
			}

			//then we do check the path itself for any obstacles
			for (int y = yStart; y < yEnd; y++, x--)
			{//checks if the in-between tiles have a piece on it
				enteredLoop = true;				
				if (board->getTileState(Vec2I(x, y)).containPiece)
					return false;
				lastX = x;
				lastY = y;				
			}
			if (enteredLoop)//if we get out of the loop, then everything is good
				return true;
			else
				return false;
		}
	}
	else //going left
	{
		if (newLocation.y > curLocation.y) //going down left
		{
			// start from current location then x decrease to the newLocation
			int x = curLocation.x - 1;
			lastX = curLocation.x;	
			//first we check its diagonal move
			for (int y = yStart,tempX = x; y <= yEnd; y++, tempX--)
			{
				if (y == yEnd) //at last point (after moving diagonally)
					if (newLocation != Vec2I(tempX, y))  //if the last point isn't the newLocation then thats mean its not a diagonalic move
						return false;						
			}

			//then we do check the path itself for any obstacles
			for (int y = yStart; y < yEnd ; y++, x--)
			{//checks if the in-between tiles have a piece on it
				enteredLoop = true;
				if (board->getTileState(Vec2I(x, y)).containPiece)
					return false;				
				lastX = x;
				lastY = y;				
			}
			if (enteredLoop)//if we get out of the loop, then everything is good
				return true;
			else
				return false;
		}
		else //going up left
		{
			// start from newlocation then x increase to the current piece location
			int x = newLocation.x + 1;
			lastX = newLocation.x;

			//first we check its diagonal move
			for (int y = yStart, tempX = x; y <= yEnd; y++, tempX++)
			{
				if (y == yEnd) //at last point (after moving diagonally)
					if (curLocation != Vec2I(tempX, y))  //if the last point isn't the curLocation then thats mean its not a diagonalic move
						return false;
			}

			//then we do check the path itself for any obstacles
			for (int y = yStart; y < yEnd; y++, x++)
			{//checks if the in-between tiles have a piece on it
				enteredLoop = true;
				if (board->getTileState(Vec2I(x, y)).containPiece)
					return false;
				lastX = x;
				lastY = y;				
			}
			if (enteredLoop)//if we get out of the loop, then everything is good
				return true;
			else
				return false;
		}
	}
}
bool Bishop::isWayClear(int newLocation) const
{
	return isWayClear(TransLocation(newLocation));
}



void Bishop::moveTo(Vec2I newLocation)
{
	if (isValidLocation(newLocation))
	{
		oldLocation = curLocation;
		curLocation = newLocation;
		reportChange();
	}
}
void Bishop::moveTo(int newLocation)
{
	moveTo(TransLocation(newLocation));
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

