#include "QueenLeg.h"



QueenLeg::QueenLeg(Vec2I curLocation, GlobalEnums::Team enemyTeam, const Board& board)
	:
	LocationValidator(curLocation, enemyTeam, board)
{
}


QueenLeg::~QueenLeg()
{
}

bool QueenLeg::IsValidLocation(Vec2I newLocation) const
{
	if (board.IsInsideTheBoard(newLocation))
	{
		//should be copied from this!!
		KingLeg kingLeg(curLocation, enemyTeam, board);

		//figuring out which team this piece is?!
		GlobalEnums::Team team = GlobalEnums::Team::BLACK;
		if (enemyTeam == GlobalEnums::Team::BLACK)
			team = GlobalEnums::Team::WHITE;

		bool notFriendly = board.GetTileState(newLocation).pieceTeam != team;
		if (kingLeg.IsValidLocation(newLocation) && notFriendly)
			return true;
		else if (IsWayClear(newLocation) && notFriendly) //checks type of move (bishop/rook) and the way itself
			return true;
		else
			return false;
	}
	else
		return false;
}

bool QueenLeg::IsWayClear(Vec2I newLocation) const
{
	//should be copied from this!!
	RookLeg rookLeg(curLocation,enemyTeam,board);
	BishopLeg bishopLeg(curLocation, enemyTeam, board);

	if (newLocation.x == curLocation.x || newLocation.y == curLocation.y)
		if (rookLeg.IsValidLocation(newLocation))
			return true;
		else
			return false;
	else if (bishopLeg.IsValidLocation(newLocation))
		return true;
	else
		return false;
}
