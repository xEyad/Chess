#include "OptionsMenu.h"

OptionsMenu::OptionsMenu(const TextSurface::Font* font)
	:
	//font(L"times", 20),
	textClr(Colors::White),
	prompt(L"Choose which board do you want to play on", Vec2I(90, 60), font, textClr),
	firstPrevBox(90, 280 +70),
	firstPrevLbl(firstPrevBox.x + 20, firstPrevBox.y - 63 ),
	prevBoxSide(118),
	prevBoxSepDist(10 + prevBoxSide),
	prevLblSepDist(130),
	prevBoxHighlight(Colors::Black),

	stoneGrey(Text(L"Stone\nGrey ", firstPrevLbl, font, textClr),
		GuidedButton(Button::CreateTextlessButton(prevBoxSide, prevBoxSide), firstPrevBox, true, prevBoxHighlight, "stoneGreyBtn"),
		GuidedSurface(new Surface(Surface::FromFile(L"D:\\workshop\\Chess\\Engine\\Resources\\images\\prevStoneGrey.png")), firstPrevBox)),

	stoneBlue(Text(L"Stone\nBlue ", { firstPrevLbl.x + prevLblSepDist , firstPrevLbl.y }, font, textClr),
		GuidedButton(Button::CreateTextlessButton(prevBoxSide, prevBoxSide), Vec2I(firstPrevBox.x + prevBoxSepDist, firstPrevBox.y), true, prevBoxHighlight, "stoneBlueBtn"),
		GuidedSurface(new Surface(Surface::FromFile(L"D:\\workshop\\Chess\\Engine\\Resources\\images\\prevStoneBlue.png")), Vec2I(firstPrevBox.x + prevBoxSepDist, firstPrevBox.y))),

	stoneBlack(Text(L"Stone\nBlack ", { firstPrevLbl.x + prevLblSepDist * 2 , firstPrevLbl.y }, font, textClr),
		GuidedButton(Button::CreateTextlessButton(prevBoxSide, prevBoxSide), Vec2I(firstPrevBox.x + prevBoxSepDist * 2, firstPrevBox.y), true, prevBoxHighlight, "stoneBlackBtn"),
		GuidedSurface(new Surface(Surface::FromFile(L"D:\\workshop\\Chess\\Engine\\Resources\\images\\prevStoneBlack.png")), Vec2I(firstPrevBox.x + prevBoxSepDist * 2, firstPrevBox.y))),

	wood(Text(L"Wood ", { firstPrevLbl.x + prevLblSepDist * 3 -10 , firstPrevLbl.y +20 }, font, textClr),
		GuidedButton(Button::CreateTextlessButton(prevBoxSide, prevBoxSide), Vec2I(firstPrevBox.x + prevBoxSepDist * 3, firstPrevBox.y), true, prevBoxHighlight, "woodBtn"),
		GuidedSurface(new Surface(Surface::FromFile(L"D:\\workshop\\Chess\\Engine\\Resources\\images\\prevWood.png")), Vec2I(firstPrevBox.x + prevBoxSepDist * 3, firstPrevBox.y))),


	backBtn(Button(119, 60, L"Back",textClr,Colors::Green,Colors::Green,false,false), { 280,530 }, true, prevBoxHighlight, "backBtn",true),
	background(new Surface(Surface::FromFile(L"D:\\workshop\\Chess\\Engine\\Resources\\images\\optionsMenu.jpg")),Vec2I(0,0))
{
	buttons.push_back(stoneGrey.btn);
	buttons.push_back(stoneBlue.btn);
	buttons.push_back(stoneBlack.btn);
	buttons.push_back(wood.btn);
	buttons.push_back(backBtn);

	sprites.push_back(background);
	sprites.push_back(stoneGrey.img);
	sprites.push_back(stoneBlue.img);
	sprites.push_back(stoneBlack.img);
	sprites.push_back(wood.img);

	messages.push_back(stoneGrey.lbl);
	messages.push_back(stoneBlue.lbl);
	messages.push_back(stoneBlack.lbl);
	messages.push_back(wood.lbl);
	messages.push_back(prompt);
}


OptionsMenu::~OptionsMenu()
{
}
