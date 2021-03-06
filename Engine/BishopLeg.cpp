#include "BishopLeg.h"



BishopLeg::BishopLeg(Vec2I curLocation, GlobalEnums::Team enemyTeam, const Board & board)
	:
	LocationValidator(curLocation, enemyTeam, board)
{

}

BishopLeg::~BishopLeg()
{
}

bool BishopLeg::IsValidLocation(Vec2I newLocation) const
{
	if (board.IsInsideTheBoard(newLocation))
	{
		//figuring out which team this piece is?!
		GlobalEnums::Team team = GlobalEnums::Team::BLACK;
		if (enemyTeam == GlobalEnums::Team::BLACK)
			team = GlobalEnums::Team::WHITE;

		if (curLocation.x == newLocation.x || curLocation.y == newLocation.y) //if same Y or X
			return false;
		else
		{
			int xDiff = abs(curLocation.x - newLocation.x);
			int yDiff = abs(curLocation.y - newLocation.y);
			if (xDiff == 1 && yDiff == 1 && board.GetTileState(newLocation).pieceTeam != team) //diagonalic ONE move just ONE
			{
				return true;
			}
			else if (IsWayClear(newLocation) && board.GetTileState(newLocation).pieceTeam != team) //if the way is clear and there is no friend on it(new tile)
				return true;
			else
				return false;
		}
	}
	else //out of board
		return false;
}

bool BishopLeg::IsWayClear(Vec2I newLocation) const
{
	//checks for diagonalic move(s)
	int yStart = min(curLocation.y, newLocation.y) + 1; //we start at the lowest Y
	int yEnd = max(curLocation.y, newLocation.y); //is the place of the other piece
	int lastY = yStart - 1;
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
				if (board.GetTileState(Vec2I(x, y)).containPiece)
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
				if (board.GetTileState(Vec2I(x, y)).containPiece)
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
			for (int y = yStart, tempX = x; y <= yEnd; y++, tempX--)
			{
				if (y == yEnd) //at last point (after moving diagonally)
					if (newLocation != Vec2I(tempX, y))  //if the last point isn't the newLocation then thats mean its not a diagonalic move
						return false;
			}

			//then we do check the path itself for any obstacles
			for (int y = yStart; y < yEnd; y++, x--)
			{//checks if the in-between tiles have a piece on it
				enteredLoop = true;
				if (board.GetTileState(Vec2I(x, y)).containPiece)
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
				if (board.GetTileState(Vec2I(x, y)).containPiece)
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
