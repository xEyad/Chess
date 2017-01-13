#pragma once
//there should be no more than ONE object of this class
class GameDirector
{
public:
	GameDirector();
	static void addTurn();
public:
	static int gameTurn;
};

