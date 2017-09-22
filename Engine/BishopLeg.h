#pragma once
#include "LocationValidator.h"
class BishopLeg :public LocationValidator
{
public:
	BishopLeg(Vec2I curLocation, GlobalEnums::Team enemyTeam, const Board& board);
	~BishopLeg();
	bool IsValidLocation(Vec2I newLocation) const;;
private:
	bool IsWayClear(Vec2I newLocation) const;
};

