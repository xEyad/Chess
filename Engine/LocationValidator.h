#pragma once
#include "Vec2.h"
#include "Board.h"
#include "GlobalEnums.h"
class LocationValidator
{
public:
	LocationValidator(Vec2I curLocation,GlobalEnums::Team enemyTeam,  const Board& board);
	virtual bool IsValidLocation(Vec2I newLocation) const = 0;
	virtual ~LocationValidator();
protected:
	Vec2I curLocation;
	const Board& board;
	GlobalEnums::Team enemyTeam;
};

