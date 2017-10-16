#pragma once
#include <iostream>
#include <fstream>
#include <sstream>
#include <cstdio>
#include <memory>
#include <string>
#include <vector>
#include "GlobalEnums.h"
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Bishop.h"
#include "King.h"
#include "Queen.h"
#include "Knight.h"
class IOManager
{
public:
	IOManager(std::string quickSaveLocation);
	IOManager();
	~IOManager();

	void SaveGame(std::string saveFile,GameState gameInfo);
	void QuickSaveGame(GameState gameInfo);
	GameState LoadGame(std::string saveFile);
	GameState QuickLoadGame();
private:
	std::stringstream ExtractInfo(std::shared_ptr<Piece> piece);
	std::stringstream ExtractInfo(GameState info);
private:
	std::string quickSaveLocation;
};
