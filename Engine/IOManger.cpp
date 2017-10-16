#include "IOManger.h"

IOManager::IOManager(std::string quickSaveLocation)
	:
	quickSaveLocation(quickSaveLocation)
{
}

IOManager::IOManager()
	:
	IOManager("../Quick Save.txt")
{
	
}

IOManager::~IOManager()
{
}

void IOManager::SaveGame(std::string saveFile, GameState gameInfo)
{
	//open file
	std::ofstream file(saveFile);

	//save operation
	for each (auto piece in gameInfo.pieces)
		file << ExtractInfo(piece).rdbuf();

	
	file << ExtractInfo(gameInfo).rdbuf();

	file.close();

}

void IOManager::QuickSaveGame(GameState gameInfo)
{
	SaveGame(quickSaveLocation, gameInfo);
}

GameState IOManager::LoadGame(std::string saveFile)
{
	using namespace std;
	//open file
	ifstream loadFile(saveFile);
	GlobalEnums::GameState loadedState;
	loadedState.board = std::make_shared<Board>(Board(8,8)); //jeap allocation is done by make_shared

	//check if its there
	if (loadFile)
	{
		//clear remove all pieces from the game
		string type, team, locationX, locationY, nStepsMoved, turn;
		int round = 0;

		//Read operation
		while (loadFile)
		{
			if (round == 0)
				loadFile >> type;
			else if (round == 1)
				loadFile >> team;
			else if (round == 2)
				loadFile >> locationX;
			else if (round == 3)
				loadFile >> locationY;
			else if (round == 4)
				loadFile >> nStepsMoved;
			round++;
			//means we got all the data we want
			if (round > 4)
			{
				int x = std::stoi(locationX);
				int y = std::stoi(locationY);
				int steps = std::stoi(nStepsMoved);
				auto Team = GetTeamFromText(team);
				auto pieceType = GetPieceTypeFromText(type);
				//check type
				switch (pieceType)
				{
					case GlobalEnums::PAWN:
						loadedState.pieces.push_back(std::shared_ptr<Pawn>(new Pawn(Vec2I{ x,y }, Team,loadedState.board.get(), steps)));
						break;
					case GlobalEnums::KNIGHT:
						loadedState.pieces.push_back(std::shared_ptr<Knight>(new Knight(Vec2I{ x,y }, Team, loadedState.board.get())));
						break;
					case GlobalEnums::ROOK:
						loadedState.pieces.push_back(std::shared_ptr<Rook>(new Rook(Vec2I{ x,y }, Team, loadedState.board.get())));
						break;
					case GlobalEnums::BISHOP:
						loadedState.pieces.push_back(std::shared_ptr<Bishop>(new Bishop(Vec2I{ x,y }, Team, loadedState.board.get())));
						break;
					case GlobalEnums::QUEEN:
						loadedState.pieces.push_back(std::shared_ptr<Queen>(new Queen(Vec2I{ x,y }, Team, loadedState.board.get())));
						break;
					case GlobalEnums::KING:
						loadedState.pieces.push_back(std::shared_ptr<King>(new King(Vec2I{ x,y }, Team, loadedState.board.get())));
						break;
					case GlobalEnums::NOT_DEFINED:
						break;
					default:
						break;
				}
				round = 0;
			}

			loadFile >> turn;
			if (turn == "turn")
				loadFile >> loadedState.turn;
			else
			{
				for each(auto c in turn)
					loadFile.unget();  // remove the extracted characters 1 by 1
				loadFile.unget();		// remove the white space behind it
			}
		}

		loadFile.close();		
	}
	
	return loadedState;
}

GameState IOManager::QuickLoadGame()
{
	return LoadGame(quickSaveLocation);
}

std::stringstream IOManager::ExtractInfo(std::shared_ptr<Piece> piece)
{
	using namespace std;
	stringstream dataStream;
	string type(GetTextForpieceType(piece->GetType()));
	string team(GetTextForTeam((int)piece->GetTeam()));
	string location(to_string(piece->Locate().x) + ' ' + to_string(piece->Locate().y));
	string nStepsMoved;
	if (dynamic_pointer_cast<Pawn> (piece))
		nStepsMoved = to_string(dynamic_pointer_cast<Pawn> (piece)->nStepsMoved());
	else
		nStepsMoved = '0';

	string line(type + ' ' + team + ' ' + location + ' ' + nStepsMoved);
	dataStream << line << " \n";
	return dataStream;
}

std::stringstream IOManager::ExtractInfo(GameState info)
{
	std::stringstream dataStream; 
	dataStream <<"turn " <<  info.turn << " \n";
	return dataStream;
}
