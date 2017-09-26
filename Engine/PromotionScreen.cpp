#include "PromotionScreen.h"

PromotionScreen::PromotionScreen(int width, int height, Graphics& gfx, Color textClr )
	:
	GameScreen(width, height,  gfx),
	font(L"times",20),
	textClr(textClr)
{
}



PromotionScreen::~PromotionScreen()
{
}

void PromotionScreen::Draw(Vec2I topLeft)
{
	GameScreen::Draw(topLeft); //just sets curTopLeft and screenRect
	static Vec2I botRight{ topLeft.x + width,topLeft.y + height };

	static RectI rook	({ topLeft.x 		 , topLeft.y }, { topLeft.x + 80	 , botRight.y });
	static RectI knight ({ topLeft.x + 80	 , topLeft.y }, { topLeft.x + 80 * 2 , botRight.y });
	static RectI bishop ({ topLeft.x + 80 * 2, topLeft.y }, { topLeft.x + 80 * 3 , botRight.y });
	static RectI queen	({ topLeft.x + 80 * 3, topLeft.y }, { topLeft.x + 80 * 4 , botRight.y });
	promotionRects = { rook,knight,bishop,queen };

	gfx.DrawTextW(L"Choose The Type of promotion", { (float)topLeft.x - 20.0f,(float)topLeft.y - 40.0f }, font, textClr);

	/*
	
	// check if mouse is inside any rect	
	for each (auto rec in promotionRects)
	{
		if (rec.Contains(mousPos))
			gfx.DrawRect(rec, highlightClr);
		else
			gfx.DrawRect(rec, edgesClr);
	}
	*/
}

std::vector<RectI> PromotionScreen::PromotionRects() const
{
	return promotionRects;
}
