#include "RookLeg.h"


RookLeg::RookLeg(Vec2I curLocation, GlobalEnums::Team enemyTeam, const Board & board)
	:
	LocationValidator(curLocation, enemyTeam,board)
{
	
}

bool RookLeg::IsValidLocation(Vec2I newLocation) const
{
	if (board.IsInsideTheBoard(newLocation))
	{
		auto tile = board.GetTileState(newLocation);
		if (!tile.containPiece || (tile.containPiece && tile.pieceTeam == enemyTeam)) //if it have no piece on it or have a piece of other team
		{
			if (curLocation.x == newLocation.x && curLocation.y != newLocation.y)
			{//moving only vertically
				if (IsWayClear(newLocation))
					return true;
				else
					return false;
			}
			else if (curLocation.x != newLocation.x && curLocation.y == newLocation.y)
			{//moving only horizontally
				if (IsWayClear(newLocation))
					return true;
				else
					return false;
			}
			else
			{
				return false;
			}
		}
		else //the tile contain a piece of the same team
			return false;
	}
	else //newLocation is out of board range
		return false;
}

RookLeg::~RookLeg()
{
}

bool RookLeg::IsWayClear(Vec2I newLocation) const
{
	if (newLocation.x == curLocation.x) //then its a vertical move (Y)
	{

		for (int y = min(curLocation.y, newLocation.y) + 1; y < max(curLocation.y, newLocation.y); y++)
		{//start from the lowest to bigger. checks if any of those tiles have a piece on it
			if (board.GetTileState(Vec2I(curLocation.x, y)).containPiece)
				return false;
		}
		//if we get out of the loop then the way is clear
		return true;
	}
	else if (newLocation.y == curLocation.y) //then its a horizontal move (X)
	{
		for (int x = min(curLocation.x, newLocation.x) + 1; x < max(curLocation.x, newLocation.x); x++)
		{//start from the lowest to bigger. checks if any of those tiles have a piece on it
			if (board.GetTileState(Vec2I(x, curLocation.y)).containPiece) //we dont check the last point
				return false;
		}
		//if we get out of the loop then the way is clear
		return true;
	}
	else
		return false;
}
