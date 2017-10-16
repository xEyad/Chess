#pragma once
#include <vector>
#include <memory>
class Board;
class Piece;
namespace GlobalEnums
{

	struct GameState
	{
		int turn = -1;
		std::vector<std::shared_ptr<Piece>> pieces;
		std::shared_ptr<Board> board = nullptr;
	};

	enum pieceType
	{
		PAWN,
		KNIGHT,
		ROOK,
		BISHOP,
		QUEEN,
		KING,
		NOT_DEFINED
	};
	constexpr char * pieceTypeStrings[] = { "PAWN","KNIGHT","ROOK","BISHOP","QUEEN","KING","NOT_DEFINED" };
	enum class Team
	{
		WHITE,
		BLACK,
		INVALID
	};
	constexpr char * teamStrings[] = { "WHITE","BLACK","INVALID" };

	inline char * GetTextForpieceType(int enumVal)
	{
		return GlobalEnums::pieceTypeStrings[enumVal];
	}  
	inline char * GetTextForTeam(int enumVal)
	{
		return GlobalEnums::teamStrings[enumVal];
	}  
	inline Team GetTeamFromText(std::string team)
	{		
		if (team == "BLACK" || team == "black")		
			return GlobalEnums::Team::BLACK;
		
		else if (team == "WHITE" || team == "white")		
			return GlobalEnums::Team::WHITE;
		else
			return GlobalEnums::Team::INVALID;
	}

	inline pieceType GetPieceTypeFromText(std::string type)
	{
		if (type == "PAWN" || type == "pawn")
			return GlobalEnums::pieceType::PAWN;
		else if (type == "ROOK" || type == "rook")
			return GlobalEnums::pieceType::ROOK;
		else if (type == "BISHOP" || type == "bishop")
			return GlobalEnums::pieceType::BISHOP;
		else if (type == "KING" || type == "king")
			return GlobalEnums::pieceType::KING;
		else if (type == "KNIGHT" || type == "knight")
			return GlobalEnums::pieceType::KNIGHT;
		else if (type == "QUEEN" || type == "queen")
			return GlobalEnums::pieceType::QUEEN;
		else
			return GlobalEnums::pieceType::NOT_DEFINED;
	}
}
