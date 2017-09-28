#pragma once
#include "PromotionScreen.h"
class WhitePromotionScreen :	public PromotionScreen
{
public:
	WhitePromotionScreen(int width, int height, Color textClr = Colors::Orange);
	~WhitePromotionScreen();
};

