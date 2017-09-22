#pragma once
#include "LocationValidator.h"
class RookLeg :	public LocationValidator
{
public:
	RookLeg(Vec2I curLocation, GlobalEnums::Team enemyTeam, const Board& board);
	virtual bool IsValidLocation(Vec2I newLocation) const;
	~RookLeg();
private:
	bool IsWayClear(Vec2I newLocation) const;
	
};

