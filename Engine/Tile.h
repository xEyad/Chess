#pragma once
#include "Colors.h"
#include "Vec2.h"
class Tile
{
public:
	Tile(Vec2I location, Color c)
		:
		color(c),
		location(location)
	{}

public:
	const Color color;
	const Vec2I location;
};