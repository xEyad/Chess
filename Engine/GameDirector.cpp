#include "GameDirector.h"

GameDirector::GameDirector()
{
}

void GameDirector::addTurn()
{
	gameTurn++;
}
int GameDirector::gameTurn = 1;