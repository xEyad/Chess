#pragma once
#include "GameScreen.h"
#include <random>
#include "Graphics.h"
class GameOver : public GameScreen
{
public:
	GameOver(const TextSurface::Font* font);
	~GameOver();
};

