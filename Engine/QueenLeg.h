#pragma once
#include "LocationValidator.h"
#include "BishopLeg.h"
#include "RookLeg.h"
#include "KingLeg.h"
class QueenLeg : public LocationValidator
{
public:
	QueenLeg(Vec2I curLocation, GlobalEnums::Team enemyTeam, const Board& board);
	~QueenLeg();
	bool IsValidLocation(Vec2I newLocation) const;
private:
	bool IsWayClear(Vec2I newLocation) const;
};

