#include "ScreenPainter.h"


ScreenPainter::ScreenPainter(Graphics & gfx)
	:
	Painter(gfx),
	btnsEdgeClr(Colors::White)
{
}

ScreenPainter::~ScreenPainter()
{
}

void ScreenPainter::DrawScreen(GameScreen& screen, Vec2I topLeft)
{
	DrawSprites(screen,topLeft);
	DrawTexts(screen); 
	DrawButtons(screen,topLeft);

	//texts are -generally- wString and position
	//gfx.DrawTextW(L"Choose The Type of promotion", { (double)topLeft.x - 20.0f,(double)topLeft.y - 40.0f }, font, textClr);
}

void ScreenPainter::SetButtonsEdgeClr(Color clr)
{
	btnsEdgeClr = clr;
}

void ScreenPainter::DrawSprites(const GameScreen& screen, Vec2I topLeft)
{
	//should handle case of multiple sprites per screen (usually using an offset inside screen object itself)
	for each (const auto Gsprite in screen.GuidedSprites())
	{
		auto clipRect = RectI(0, Graphics::ScreenHeight, 0, Graphics::ScreenWidth);
		gfx.DrawSpriteClipped(Gsprite.surface,topLeft + Gsprite.topLeftOffset, clipRect);
	}	
	/*
	gfx.DrawTextW(L"Choose The Type of promotion", { (float)topLeft.x - 20.0f,(float)topLeft.y - 40.0f }, font, textClr);

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

void ScreenPainter::DrawTexts(const GameScreen & screen)
{
}

void ScreenPainter::DrawButtons(const GameScreen & screen, Vec2I topLeft)
{
	for each (auto mpdBtn in screen.MappedButtons())
	{	
		auto bb = mpdBtn.btn.GetBoundingBox(topLeft);
		auto xOffset = mpdBtn.topLeftOffset.x;
		auto yOffset = mpdBtn.topLeftOffset.y;
		bb = RectI( bb.top + yOffset,bb.bottom + yOffset,bb.left + xOffset,bb.right + xOffset );
		gfx.DrawRect(bb, btnsEdgeClr);
	}
	/*if (offsetX > width)
		offsetX = 0;
	if (offsetY > height)
		offsetY = 0;

	gfx.DrawText(L"Start", Vec2I(location.x + offsetX, location.y + offsetY), font, textClr);*/
}
