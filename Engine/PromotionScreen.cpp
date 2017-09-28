#include "PromotionScreen.h"

PromotionScreen::PromotionScreen(int width, int height, Color textClr )
	:
	GameScreen(width, height),
	font(L"times",20),
	textClr(textClr),
	sprite(nullptr),
	spriteOffset(0,0),
	rookBtn(Button(80, 80), Vec2I(0,0) + spriteOffset),
	knightBtn(Button(80, 80), Vec2I(80, 0) + spriteOffset),
	bishopBtn(Button(80, 80), Vec2I(80*2, 0) + spriteOffset),
	queenBtn(Button( 80,80 ), Vec2I( 80*3, 0) + spriteOffset)
{
	buttons.push_back(rookBtn);
	buttons.push_back(knightBtn);
	buttons.push_back(bishopBtn);
	buttons.push_back(queenBtn);
}



PromotionScreen::~PromotionScreen()
{
}

