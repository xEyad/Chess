#pragma once
#include "PromotionScreen.h"
class WhitePromotionScreen :	public PromotionScreen
{
public:
	WhitePromotionScreen(int width, int height, Graphics& gfx, Color textClr = Colors::Orange);
	~WhitePromotionScreen();
	virtual void Draw(Vec2I topLeft) override;
private:
	Surface* const WpromotionScreen;
};

