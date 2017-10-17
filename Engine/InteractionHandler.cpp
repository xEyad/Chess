#include "InteractionHandler.h"


InteractionHandler::InteractionHandler(Mouse& mouse, Keyboard& kbd)
	:
	mouse(mouse),
	kbd(kbd)
{
}

InteractionHandler::~InteractionHandler()
{
}

std::string InteractionHandler::HandleMouseInput(GameScreen& screen,Vec2I topLeft)
{
	for each (auto mpdBtn in screen.MappedButtons())
	{
		if (mouse.LeftIsPressed() && mpdBtn.GetBoundingBox(topLeft).Contains(mouse.GetPos()))
		{
			return mpdBtn.name;
		}
	}
	return "";
}
