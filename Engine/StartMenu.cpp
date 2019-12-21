#include "StartMenu.h"

StartMenu::StartMenu()
	:
	screenCenter((int)(Graphics::ScreenWidth / 2), (int)(Graphics::ScreenHeight / 2)),
	btnsHighlight(Colors::Cyan),
	btnsTxtClr(Colors::White),
	btnsEdgesClr(Colors::White),
	btnsWidth(180),
	btnsHeight(40),
	btnsTopLeftOffset(screenCenter.x - btnsWidth / 2, screenCenter.y - btnsHeight / 2),
	btnsSepartaionDist(btnsHeight + 50),
	playBtn(Button(btnsWidth, btnsHeight, L"Play", btnsTxtClr, btnsEdgesClr,Colors::White,false,false),
	{ btnsTopLeftOffset.x,btnsTopLeftOffset.y - btnsSepartaionDist }, true, btnsHighlight, "playBtn", true),

	optBtn(Button(btnsWidth, btnsHeight, L"Options", btnsTxtClr, btnsEdgesClr, Colors::White, false, false),
	{ btnsTopLeftOffset.x - 20,btnsTopLeftOffset.y }, true, btnsHighlight, "optBtn", true),

	exitBtn(Button(btnsWidth, btnsHeight, L"Exit", btnsTxtClr, btnsEdgesClr, Colors::White, false, false),
	{ btnsTopLeftOffset.x,btnsTopLeftOffset.y + btnsSepartaionDist }, true, btnsHighlight,"exitBtn",true),

	backgroundSprite(new Surface(Surface::FromFile(L"Resources\\images\\startMenu.jpg")), Vec2I( 0,0 ))
{
	buttons.push_back(playBtn);
	buttons.push_back(optBtn);
	buttons.push_back(exitBtn);
	sprites.push_back(backgroundSprite);
}