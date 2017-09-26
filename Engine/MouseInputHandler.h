#pragma once
#include "Mouse.h"
#include "GameScreen.h"
//this class takes a GameScreen and return desired data about mouse interaction with it
class MouseInputHandler
{
public:
	MouseInputHandler(Mouse& m);
	~MouseInputHandler();
	Vec2I MousePos(const GameScreen& gameScreen);
private:
	Mouse& mouse;
};

