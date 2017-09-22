#include "LocationValidator.h"



LocationValidator::LocationValidator(Vec2I curLocation, GlobalEnums::Team enemyTeam,  const Board& board)
	:
	curLocation(curLocation),
	board(board),
	enemyTeam(enemyTeam)
{
}


LocationValidator::~LocationValidator()
{
}
