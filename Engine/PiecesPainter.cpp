#include "PiecesPainter.h"



PiecesPainter::PiecesPainter(Graphics & gfx, const std::vector<std::shared_ptr<Piece>>* pieces)
	:
	Painter(gfx),
	pieces(pieces)
{
	ChangeStyleTo(1);
}

PiecesPainter::~PiecesPainter()
{
}

void PiecesPainter::DrawPiecesSquares(Vec2I topLeft)
{
	int tileWidth = Board::GetTileWidth();
	int tileHeight = Board::GetTileHeight();
	Color c;
	Vec2I screenLocation = topLeft;
	for (auto i = pieces->cbegin(); i < pieces->cend(); i++)
	{
		if ((*i)->isCaptured() == false )
		{
			//give it a color based on its type
			switch ((*i)->GetType())
			{
				case QUEEN:
					c = Colors::Red;
					break;
				case KING:
					c = Colors::Magenta;
					break;
				case BISHOP:
					c = Colors::Cyan;
					break;
				case ROOK:
					c = Colors::Yellow;
					break;
				case PAWN:
					c = Colors::Green;
					break;
				case KNIGHT:
					c = Colors::LightGray;
					break;
				default:
					c = Colors::Black;
					break;
			}
			Vec2I centerPoint(screenLocation.x + (*i)->Locate().x * tileWidth + (tileWidth / 2), screenLocation.y + (*i)->Locate().y * tileHeight + (tileHeight / 2));
			int size = tileWidth / 4;
			RectI r(centerPoint.y - size, centerPoint.y + size, centerPoint.x - size, centerPoint.x + size);
			gfx.DrawColoredRect(r, c);
		}
	}
}

void PiecesPainter::DrawPiecesSprites(Vec2I topLeft)
{
	int tileWidth = Board::GetTileWidth();
	int tileHeight = Board::GetTileHeight();
	Color c;
	Vec2I screenLocation = topLeft;
	for (auto pPiece = pieces->cbegin(); pPiece < pieces->cend(); pPiece++)
	{
		if ((*pPiece)->isCaptured() == false)
		{
			auto sprite = GetSprite(pPiece->get());
			auto sprWidth = sprite->GetWidth();
			auto sprHeight = sprite->GetHeight();
			
			//top left point of the tile which the piece is on
			Vec2I topLeftPoint(screenLocation.x + (*pPiece)->Locate().x * tileWidth, screenLocation.y + (*pPiece)->Locate().y * tileHeight);

			int xPieceSpr = 0;
			int yPieceSpr = 0;
			for (unsigned int x = topLeftPoint.x; x < sprWidth - 1 + topLeftPoint.x; x++)
			{
				for (unsigned int y = topLeftPoint.y; y < sprHeight - 1 + topLeftPoint.y; y++)
				{
					gfx.PutPixelAlphaClipped(x, y, sprite->GetPixel(xPieceSpr, yPieceSpr), RectI(0, Graphics::ScreenHeight, 0, Graphics::ScreenWidth));
					yPieceSpr++;
				}
				xPieceSpr++;
				yPieceSpr = 0;
			}
		}
		else
			continue;
	}
}

void PiecesPainter::DrawPiecesSprites(Vec2I topLeft, int styleNum)
{
	DeleteSprites();
	ChangeStyleTo(styleNum);
	DrawPiecesSprites(topLeft);
}
void PiecesPainter::ChangeStyleTo(int styleNum)
{	
	switch (styleNum)
	{
		case 1:
			wPawnSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Stone\\PawnW.png"));
			wRookSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Stone\\RookW.png"));
			wKnightSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Stone\\KnightW.png"));
			wBishopSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Stone\\BishopW.png"));
			wQueenSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Stone\\QueenW.png"));
			wKingSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Stone\\KingW.png"));

			bPawnSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Stone\\PawnB.png"));
			bRookSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Stone\\RookB.png"));
			bKnightSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Stone\\KnightB.png"));
			bBishopSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Stone\\BishopB.png"));
			bQueenSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Stone\\QueenB.png"));
			bKingSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Stone\\KingB.png"));
			break;
		default: //case 2
			wPawnSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Wood\\PawnW.png"));
			wRookSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Wood\\RookW.png"));
			wKnightSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Wood\\KnightW.png"));
			wBishopSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Wood\\BishopW.png"));
			wQueenSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Wood\\QueenW.png"));
			wKingSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Wood\\KingW.png"));

			bPawnSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Wood\\PawnB.png"));
			bRookSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Wood\\RookB.png"));
			bKnightSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Wood\\KnightB.png"));
			bBishopSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Wood\\BishopB.png"));
			bQueenSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Wood\\QueenB.png"));
			bKingSpr = new Surface(Surface::FromFile(L"Resources\\Chess Pieces\\Wood\\KingB.png"));
			break;
	}
}

void PiecesPainter::DeleteSprites()
{
	delete wPawnSpr;
	delete wRookSpr;
	delete wKnightSpr;
	delete wBishopSpr;
	delete wQueenSpr;
	delete wKingSpr;

	delete bPawnSpr;
	delete bRookSpr;
	delete bKnightSpr;
	delete bBishopSpr;
	delete bQueenSpr;
	delete bKingSpr;
}

Surface* PiecesPainter::GetSprite(Piece * pPiece)
{	
	using namespace GlobalEnums;
	if (pPiece->GetTeam() == Team::WHITE)
	{
		switch (pPiece->GetType())
		{
			case pieceType::PAWN:
				return wPawnSpr;
					break;
			case pieceType::ROOK:
				return wRookSpr;
				break;
			case pieceType::KNIGHT:
				return wKnightSpr;
				break;
			case pieceType::BISHOP:
				return wBishopSpr;
				break;
			case pieceType::QUEEN:
				return wQueenSpr;
				break;
			case pieceType::KING:
				return wKingSpr;
				break;
			default:
				break;
		}
	}

	else if(pPiece->GetTeam() == Team::BLACK)
	{
		switch (pPiece->GetType())
		{
			case pieceType::PAWN:
				return bPawnSpr;
				break;
			case pieceType::ROOK:
				return bRookSpr;
				break;
			case pieceType::KNIGHT:
				return bKnightSpr;
				break;
			case pieceType::BISHOP:
				return bBishopSpr;
				break;
			case pieceType::QUEEN:
				return bQueenSpr;
				break;
			case pieceType::KING:
				return bKingSpr;
				break;
			default:
				break;
		}
	}
}
