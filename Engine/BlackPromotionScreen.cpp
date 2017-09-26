#include "BlackPromotionScreen.h"



BlackPromotionScreen::BlackPromotionScreen(int width, int height, Graphics& gfx, Color textClr )
	:
	PromotionScreen(width, height, gfx, textClr),
	BpromotionScreen(new Surface(Surface::FromFile(L"Resources\\Screens\\Promotion Screen Wood Black.png")))
{
}


BlackPromotionScreen::~BlackPromotionScreen()
{
}

void BlackPromotionScreen::Draw(Vec2I topLeft)
{
	static Vec2I botRight{ topLeft.x + width,topLeft.y + height };

	int xPieceSpr = 0;
	int yPieceSpr = 0;
	for (unsigned int x = topLeft.x; x < BpromotionScreen->GetWidth() + topLeft.x; x++)
	{
		for (unsigned int y = topLeft.y; y < BpromotionScreen->GetHeight() + topLeft.y; y++)
		{
			gfx.PutPixelAlphaClipped(x, y, BpromotionScreen->GetPixel(xPieceSpr, yPieceSpr), RectI(0, Graphics::ScreenHeight, 0, Graphics::ScreenWidth));
			yPieceSpr++;
		}
		xPieceSpr++;
		yPieceSpr = 0;
	}

	PromotionScreen::Draw(topLeft);

}