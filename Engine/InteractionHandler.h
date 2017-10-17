#pragma once
#include "Mouse.h"
#include "Keyboard.h"
#include "GameScreen.h"
class InteractionHandler
{
public:
	InteractionHandler(Mouse& mouse,Keyboard& kbd);
	~InteractionHandler();

	//tells which clickable objects is clicked
	std::string HandleMouseInput(GameScreen& screen, Vec2I topLeft);
private:
	Mouse& mouse;
	Keyboard& kbd;
};
