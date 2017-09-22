#include "KingLeg.h"


KingLeg::KingLeg(Vec2I curLocation, GlobalEnums::Team enemyTeam, const Board& board)
	:
	LocationValidator( curLocation,  enemyTeam, board)
{}


KingLeg::~KingLeg()
{
}

bool KingLeg::IsValidLocation(Vec2I newLocation) const
{
	if (board.IsInsideTheBoard(newLocation))
	{
		//figuring out which team this piece is?!
		GlobalEnums::Team team = GlobalEnums::Team::BLACK;
		if (enemyTeam == GlobalEnums::Team::BLACK)
			team = GlobalEnums::Team::WHITE;

		int xDiff = abs(newLocation.x - curLocation.x);
		int yDiff = abs(newLocation.y - curLocation.y);
		if (xDiff <= 1 && yDiff <= 1 && board.GetTileState(newLocation).pieceTeam != team)
			return true;
		else
			return false;
	}
	else
		return false;
}

