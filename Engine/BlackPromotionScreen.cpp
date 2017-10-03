#include "BlackPromotionScreen.h"



BlackPromotionScreen::BlackPromotionScreen( Color textClr )
	:
	PromotionScreen(textClr)	
{
	//cannot intialize base class member using the child's constructor, so...
	sprite = std::make_shared<Surface>(Surface(Surface::FromFile(L"Resources\\Screens\\Promotion Screen Wood Black.png")));
	
	sprites.push_back(GuidedSurface(sprite.get(), spriteOffset));
	
	GameScreen::setHeight(sprite->GetHeight());
	GameScreen::setWidth(sprite->GetWidth());
}


BlackPromotionScreen::~BlackPromotionScreen()
{
}
