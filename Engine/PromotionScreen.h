#pragma once
#include "GameScreen.h"
#include "Surface.h"
class PromotionScreen :	public GameScreen
{
public:
	PromotionScreen(int width, int height, Graphics& gfx, Color textClr);
	~PromotionScreen();
	virtual void Draw(Vec2I topLeft) override;
	std::vector<RectI> PromotionRects() const;

private:
	std::vector<RectI> promotionRects;
	const TextSurface::Font font;
	Color textClr;
};

