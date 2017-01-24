#pragma once
//just test cases file based on a certain layout

//declerations
/*
Board chessBoard;
Pawn pawn;
Pawn pawn2;
Pawn pawn3;
Pawn pawn4;
Rook rook;
Bishop bishop;
King king;
Queen queen;
Knight knight;

// intializations
chessBoard(8, 8), //basic chess board
pawn(Vec2I(1, 1),Team::BLACK, &chessBoard),
pawn2(Vec2I(6, 1), Team::BLACK, &chessBoard),
rook(Vec2I(3,1), Team::BLACK, &chessBoard),
bishop(Vec2I(4, 3), Team::BLACK, &chessBoard),
king(Vec2I(4, 2), Team::BLACK, &chessBoard),
queen(Vec2I(1, 3), Team::BLACK, &chessBoard),
knight(Vec2I(2, 4), Team::BLACK, &chessBoard),
pawn3(Vec2I(1, 6), Team::WHITE, &chessBoard),
pawn4(Vec2I(7, 6), Team::WHITE, &chessBoard)

//tests
//fails
//	knight.moveTo({ 2,6 });
//	knight.moveTo({ 3,5 });
//	knight.moveTo({ 6,3 });
//	knight.moveTo(bishop.locate());
//	knight.moveTo({ 0,1 });
//	queen.moveTo({ pawn.locate() });
//	queen.moveTo({ rook.locate() });
//	queen.moveTo({ king.locate() });
//	queen.moveTo({ bishop.locate() });
//	queen.moveTo({ 2,5 });
//	queen.moveTo({ 5,3 });
//	queen.moveTo({ 4,0 });
//	queen.moveTo({ 5,5 });
//	bishop.moveTo({ 1,5});
//	bishop.moveTo({ 2,4 });
//	bishop.moveTo({ 7,1 });
//	bishop.moveTo({ 6,1 });
//	bishop.moveTo({ 0,1 });
//	bishop.moveTo({ 3,5 });
//	bishop.moveTo(pawn2.locate());
//	king.moveTo({ rook.locate() });
//	king.moveTo({ bishop.locate() });
//	king.moveTo({ pawn3.locate() });
//	king.moveTo({ 4,6 });

//success
//	knight.moveTo({ pawn3.locate() });
//	knight.moveTo({ 3,5 });
//	knight.moveTo({ 2,3 });
//	knight.moveTo({ 0,2 });
//	knight.moveTo({ 2,1 });
//	knight.moveTo({ 4,0 });
//	knight.moveTo({ 5,2 });
//	knight.moveTo({ 7,3 });
//	queen.moveTo({ 2,3 });
//	queen.moveTo({ 3,3 });
//	queen.moveTo({ 1,4 });
//	queen.moveTo({ 3,3 });
//	queen.moveTo({ 4,6 });
//	queen.moveTo({ 4,4 });
//	queen.moveTo({ 7,1 });
//	queen.moveTo({ 7,6 });
//	king.moveTo({ 4,1 });
//	king.moveTo({ 4,0 });
//	king.moveTo({ 5,0 });
//	king.moveTo({ 4,1 });
//	bishop.moveTo(pawn4.locate());
//	bishop.moveTo(pawn3.locate());
//	bishop.moveTo({ 5,2 });
//	bishop.moveTo({ 2,1 });
//	bishop.moveTo({ 1,6 });
//	rook.moveTo({ 3,0 });
//	rook.moveTo({ 1,4 });
//	rook.moveTo({ 1,6 });
//	rook.moveTo(pawn.locate());
//	rook.moveTo({ 0,1 });
//	rook.moveTo(pawn2.locate());
//	rook.moveTo({ 5,2 });
//	rook.moveTo({ 3,0 });
//	rook.moveTo({ 7,1 });
//	rook.moveTo({ 3,5 });
//	pawn.moveTo({ 1,3 });
//	pawn.moveTo({ 1,6 });
*/