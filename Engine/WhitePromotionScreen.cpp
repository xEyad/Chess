#include "WhitePromotionScreen.h"



WhitePromotionScreen::WhitePromotionScreen(int width, int height, Graphics& gfx, Color textClr )
	:
	PromotionScreen(width, height, gfx, textClr),
	WpromotionScreen(new Surface(Surface::FromFile(L"Resources\\Screens\\Promotion Screen Wood White.png")))
{
}


WhitePromotionScreen::~WhitePromotionScreen()
{
}

void WhitePromotionScreen::Draw(Vec2I topLeft)
{
	static Vec2I botRight{ topLeft.x + width,topLeft.y +height };

	
	int xPieceSpr = 0;
	int yPieceSpr = 0;
	for (unsigned int x = topLeft.x; x < WpromotionScreen->GetWidth() + topLeft.x; x++)
	{
		for (unsigned int y = topLeft.y; y < WpromotionScreen->GetHeight() + topLeft.y; y++)
		{
			gfx.PutPixelAlphaClipped(x, y, WpromotionScreen->GetPixel(xPieceSpr, yPieceSpr), RectI(0, Graphics::ScreenHeight, 0, Graphics::ScreenWidth));
			yPieceSpr++;
		}
		xPieceSpr++;
		yPieceSpr = 0;
	}

	PromotionScreen::Draw(topLeft);
}