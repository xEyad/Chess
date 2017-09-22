#pragma once
#include "LocationValidator.h"

class KingLeg : public LocationValidator
{
public:
	KingLeg(Vec2I curLocation, GlobalEnums::Team enemyTeam, const Board& board);
	~KingLeg();
	bool IsValidLocation(Vec2I newLocation) const;
};

