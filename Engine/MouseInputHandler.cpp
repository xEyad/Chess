#include "MouseInputHandler.h"



MouseInputHandler::MouseInputHandler(Mouse & m)
	:
	mouse(m)
{
}

MouseInputHandler::~MouseInputHandler()
{
}

Vec2I MouseInputHandler::MousePos(const GameScreen& gameScreen)
{
	if (gameScreen.Rect().Contains(mouse.GetPos()))
		return mouse.GetPos();
	else
		return{ -1,-1 };
}
