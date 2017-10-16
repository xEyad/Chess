#pragma once
#include "GameScreen.h"

class PromotionScreen :	public GameScreen
{
public:
	PromotionScreen( Color textClr);
	~PromotionScreen() = 0;


protected:
	std::shared_ptr<Surface> sprite;
	Vec2I spriteOffset;
private:
	Text title;
	const TextSurface::Font font;
	Color textClr;
	std::wstring message;
	GuidedButton rookBtn;
	GuidedButton knightBtn;
	GuidedButton bishopBtn;
	GuidedButton queenBtn;
};

