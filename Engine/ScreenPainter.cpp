#include "ScreenPainter.h"


ScreenPainter::ScreenPainter(Graphics & gfx)
	:
	Painter(gfx)
{
}

ScreenPainter::~ScreenPainter()
{
}

void ScreenPainter::DrawScreenWithHighlights(GameScreen & screen, Vec2I topLeft, Vec2I mousePos)
{
	DrawSprites(screen, topLeft);
	DrawTexts(screen, topLeft);
	DrawButtons(screen, topLeft);
	DoHighlights(screen, topLeft, mousePos);
}

void ScreenPainter::DrawScreen(GameScreen& screen, Vec2I topLeft)
{
	DrawSprites(screen,topLeft);
	DrawTexts(screen, topLeft);
	DrawButtons(screen,topLeft);
}

void ScreenPainter::DrawSprites(const GameScreen& screen, Vec2I topLeft)
{
	for each (const auto Gsprite in screen.GuidedSprites())
	{
		auto clipRect = RectI(0, Graphics::ScreenHeight, 0, Graphics::ScreenWidth);
		gfx.DrawSpriteClipped(Gsprite.surface,topLeft + Gsprite.topLeftOffset, clipRect);
	}	
}

void ScreenPainter::DrawTexts(const GameScreen & screen, Vec2I topLeft)
{
	for each (Text msg in screen.Messages())	
		gfx.DrawText(msg.content, Vec2I( msg.pos.x + topLeft.x, msg.pos.y + topLeft.y ),*(msg.font), msg.clr);
}

void ScreenPainter::DrawButtons(const GameScreen & screen, Vec2I topLeft)
{
	for each (auto mpdBtn in screen.MappedButtons())
	{	
		auto Btn = mpdBtn.btn;
		auto bb = mpdBtn.GetBoundingBox(topLeft);
		
		//Button Drawing
		if(Btn.HaveEdges())
			gfx.DrawRect(bb, mpdBtn.btn.EdgesColor());
		if (Btn.HaveFill())		
			gfx.FillRect(bb, Btn.FillColor());
		
		//draw button's text in middle
		auto btnW = bb.right - bb.left;
		auto btnH = bb.bottom - bb.top;
		Vec2I btnCenter(bb.left + btnW / 2, bb.top + btnH / 2);
		Vec2I textPlacement(int(btnCenter.x - btnW / 4), int(btnCenter.y - btnH*.4) );
		gfx.DrawText(mpdBtn.btn.Text(), textPlacement, TextSurface::Font(L"times", 20), mpdBtn.btn.TextColor());
	}
}

void ScreenPainter::DoHighlights(const GameScreen & screen, Vec2I topLeft, Vec2I mousePos)
{
	for each (auto mpdBtn in screen.MappedButtons())
	{
		if (mpdBtn.haveHighlight)
		{
			auto btn = mpdBtn.btn;
			auto bb = mpdBtn.GetBoundingBox(topLeft);
			if (bb.Contains(mousePos))
			{
				if (btn.HaveEdges())
					gfx.DrawRect(bb, mpdBtn.highlight);
				if (btn.HaveFill())
					gfx.FillRect(bb, mpdBtn.highlight);
				if (mpdBtn.highlightText)
				{
					// Re-draw button's text with new color
					auto btnW = bb.right - bb.left;
					auto btnH = bb.bottom - bb.top;
					Vec2I btnCenter(bb.left + btnW / 2, bb.top + btnH / 2);
					Vec2I textPlacement(int(btnCenter.x - btnW / 4),int(btnCenter.y - btnH*.4));
					gfx.DrawText(mpdBtn.btn.Text(), textPlacement, TextSurface::Font(L"times", 20), mpdBtn.highlight);
				}
			}
		}
	}
}
