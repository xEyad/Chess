#pragma once
#include "PromotionScreen.h"
class BlackPromotionScreen :	public PromotionScreen
{
public:
	BlackPromotionScreen(int width, int height, Graphics& gfx, Color textClr = Colors::Orange);
	~BlackPromotionScreen();
	virtual void Draw(Vec2I topLeft) override;
private:
	Surface* const BpromotionScreen;
};

