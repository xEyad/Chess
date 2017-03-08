#include "Queen.h"

Queen::Queen(Vec2I location, Team team, Board* const board, Surface* const sprite)
	:
	Piece(location, team, QUEEN, board,sprite)
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

int Queen::HowManyLeft() const
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

bool Queen::IsValidLocation(Vec2I newLocation) const
{
	if (board->IsInsideTheBoard(newLocation))
	{
		bool notFriendly = board->GetTileState(newLocation).pieceTeam != team;
		if (isKingMove(newLocation) && notFriendly)
			return true;
		else if (IsWayClear(newLocation) && notFriendly) //checks type of move (bishop/rook) and the way itself
			return true;
		else
			return false;
	}
	else
		return false;
}

bool Queen::IsWayClear(Vec2I newLocation) const
{
	if (newLocation.x == curLocation.x || newLocation.y == curLocation.y)
		if (isValidRookMove(newLocation))
			return true;
		else
			return false;
	else if (isValidBishopMove(newLocation))
		return true;
	else
		return false;
}

bool Queen::isValidRookMove(Vec2I newLocation) const
{
	if (newLocation.x == curLocation.x) //then its a vertical move (Y)
	{
		for (int i = min(curLocation.y, newLocation.y)+1; i < max(curLocation.y, newLocation.y) ; i++)
		{//start from the lowest to bigger. checks if any of those tiles have a piece on it		
			if (board->GetTileState(Vec2I(curLocation.x, i )).containPiece)
				return false;
		}
		//if we get out of the loop then the way is clear
		return true;
	}
	else if (newLocation.y == curLocation.y) //then its a horizontal move (X)
	{
		for (int i = min(curLocation.x, newLocation.x) + 1; i < max(curLocation.x, newLocation.x) ; i++)
		{//start from the lowest to bigger. checks if any of those tiles have a piece on it
			if (board->GetTileState(Vec2I(i , curLocation.y)).containPiece) //we dont check the last point
				return false;
		}
		//if we get out of the loop then the way is clear
		return true;
	}
	else
		return false;
}

bool Queen::isValidBishopMove(Vec2I newLocation) const
{
	//checks for diagonalic move(s)
	int yStart = min(curLocation.y, newLocation.y) +1; //we start at the lowest Y
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
				if (board->GetTileState(Vec2I(x, y)).containPiece)
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
				if (board->GetTileState(Vec2I(x, y)).containPiece)
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
				if (board->GetTileState(Vec2I(x, y)).containPiece)
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
				if (board->GetTileState(Vec2I(x, y)).containPiece)
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

bool Queen::isKingMove(Vec2I newLocation) const
{
	int xDiff = abs(newLocation.x - curLocation.x);
	int yDiff = abs(newLocation.y - curLocation.y);
	if (xDiff <= 1 && yDiff <= 1)
		return true;
	else
		return false;
}

bool Queen::MoveTo(Vec2I newLocation)
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

void Queen::GenerateValidMoves()
{
	validTiles.clear();
	//rook
	for (auto x = 0; x < board->rows; x++)
	{
		if (IsValidLocation({ x,curLocation.y }))
			validTiles.push_back({ x,curLocation.y });
	}
	for (auto y = 0; y < board->columns; y++)
	{
		if (IsValidLocation({ curLocation.x,y }))
			validTiles.push_back({ curLocation.x,y });
	}

	//bishop
	//x increases
	for (int upY = curLocation.y, downY = upY, x = curLocation.x; x < board->rows; x++, upY--, downY++)
	{
		if (IsValidLocation({ x,upY }))
			validTiles.push_back({ x,upY });

		if (IsValidLocation({ x,downY }))
			validTiles.push_back({ x,downY });
	}
	//x decreases
	for (int upY = curLocation.y, downY = upY, x = curLocation.x; x >= 0; x--, upY--, downY++)
	{
		if (IsValidLocation({ x,upY }))
			validTiles.push_back({ x,upY });

		if (IsValidLocation({ x,downY }))
			validTiles.push_back({ x,downY });
	}
}

Queen::~Queen()
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

int Queen::nWhiteLeft = 0;
int Queen::nBlackLeft = 0;

bool Queen::IsValidLocation(int newLocation) const
{
	return IsValidLocation(TransLocation(newLocation));
}
bool Queen::IsWayClear(int newLocation) const
{
	return IsWayClear(TransLocation(newLocation));
}
bool Queen::MoveTo(int newLocation)
{
	return MoveTo(TransLocation(newLocation));
}