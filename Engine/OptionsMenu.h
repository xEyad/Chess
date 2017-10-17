#pragma once
#include "GameScreen.h"
class OptionsMenu :	public GameScreen
{
	struct Preview
	{
		Preview(Text lbl, GuidedButton btn, GuidedSurface img)
			:
			lbl(lbl),
			btn(btn),
			img(img)
		{}
		Text lbl;
		GuidedButton btn;
		GuidedSurface img;
	};
public:
	OptionsMenu(const TextSurface::Font* font);
	~OptionsMenu();
private:
	//const TextSurface::Font font;
	Color textClr;
	Text prompt;
	Vec2I firstPrevBox;
	Vec2I firstPrevLbl;
	int prevBoxSide;
	int prevBoxSepDist;
	int prevLblSepDist;
	Color prevBoxHighlight;
	Preview stoneGrey;
	Preview stoneBlue;
	Preview stoneBlack;
	Preview wood;
	GuidedButton backBtn;
	GuidedSurface background;
};

