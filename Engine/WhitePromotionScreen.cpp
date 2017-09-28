#include "WhitePromotionScreen.h"



WhitePromotionScreen::WhitePromotionScreen(int width, int height, Color textClr )
	:
	PromotionScreen(width, height, textClr)	
{
	//cannot intialize base class member using the child's constructor, so...
	sprite = std::make_shared<Surface>(Surface(Surface::FromFile(L"Resources\\Screens\\Promotion Screen Wood White.png")));
	sprites.push_back(GuidedSurface(sprite.get(), spriteOffset));
}


WhitePromotionScreen::~WhitePromotionScreen()
{
}
