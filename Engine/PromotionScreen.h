#pragma once
#include "GameScreen.h"

class PromotionScreen :	public GameScreen
{
public:
	PromotionScreen(int width, int height, Color textClr);
	~PromotionScreen() = 0;



protected:
	std::shared_ptr<Surface> sprite;
	Vec2I spriteOffset;
private:
	const TextSurface::Font font;
	Color textClr;
	GuidedButton rookBtn;
	GuidedButton knightBtn;
	GuidedButton bishopBtn;
	GuidedButton queenBtn;
};

