#pragma once
#include "GameScreen.h"

class StartMenu : public GameScreen
{
public:
	StartMenu();

private:
	Vec2I screenCenter;
	Color btnsHighlight;
	Color btnsTxtClr;
	Color btnsEdgesClr;
	int btnsWidth;
	int btnsHeight;
	Vec2I btnsTopLeftOffset;
	int btnsSepartaionDist;
	GuidedButton playBtn;
	GuidedButton optBtn;
	GuidedButton exitBtn;
	GuidedSurface backgroundSprite;
};
