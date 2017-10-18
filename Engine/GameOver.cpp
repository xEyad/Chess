#include "GameOver.h"



GameOver::GameOver(const TextSurface::Font* font)
{
	std::random_device rd; // obtain a random number from hardware
	std::mt19937 eng(rd()); // seed the generator
	std::mt19937 eng2(rd()); // seed the generator
	std::uniform_int_distribution<> distr(0, 225); // define the range
	for (auto y = 10.0f; y < Graphics::ScreenHeight; y += 30)
	{
		Vec2I pos(int(Graphics::ScreenWidth / 2 - 80.0f), y);
		Color clr(Colors::MakeRGB(distr(eng), distr(eng) + distr(eng2), distr(eng) - distr(eng2)));
		Text t(L"GAME OVER!", pos, font, clr);
		messages.push_back(t);			
	}
	Vec2I pos(int(Graphics::ScreenWidth / 2 - 80.0f),Graphics::ScreenHeight / 2 + 30 );
	Color clr(Colors::MakeRGB(distr(eng), distr(eng) + distr(eng2), distr(eng) - distr(eng2)));
	Text t(L"GAME OVER!", pos, font, clr);
	messages.push_back(t);
}


GameOver::~GameOver()
{
}

