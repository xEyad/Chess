#include "PromotionScreen.h"

PromotionScreen::PromotionScreen(Color textClr )
	:	
	font(L"times",20),
	title(L"Choose The Type of promotion", { -20,-40 },&font, textClr),
	sprite(nullptr),
	spriteOffset(0,0),
	rookBtn(Button::CreateTextlessButton(80, 80), Vec2I(0,0) + spriteOffset,true,Colors::Green),
	knightBtn(Button::CreateTextlessButton(80, 80), Vec2I(80, 0) + spriteOffset, true, Colors::Green),
	bishopBtn(Button::CreateTextlessButton(80, 80), Vec2I(80*2, 0) + spriteOffset, true, Colors::Green),
	queenBtn(Button::CreateTextlessButton( 80,80 ), Vec2I( 80*3, 0) + spriteOffset, true, Colors::Green)
{
	buttons.push_back(rookBtn);
	buttons.push_back(knightBtn);
	buttons.push_back(bishopBtn);
	buttons.push_back(queenBtn);
	messages.push_back(title);
}



PromotionScreen::~PromotionScreen()
{
}

