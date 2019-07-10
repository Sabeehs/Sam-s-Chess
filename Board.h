#pragma once
#include "GP142.H"
#include <vector>
#include <string>
#include "Piece.h"
#include "Pawn.h"
#include "Rook.h"
#include "Knight.h"
#include "Bishop.h"
#include "Queen.h"
#include "King.h"
class Piece; 

class Board
{
public:
	Piece* pieces[8][8];
	vector <string> bDead, wDead;
	GP142_point coords[8][8] = { -1,-1 };
	int turns;
	Board();
	void initialize();
	void printBKGND();
	void print();
	bool testTurn(int x, int y, bool turn);
	bool isSafe(GP142_point currPos, int x, int y);
	bool isClear(GP142_point currPos, int x, int y);
	void move(GP142_point currPos, int x, int y);
	bool Board::isCheck(bool turn);
	bool isCheckMate(bool turn);
	bool isDraw();
	void printMoves(GP142_point p, bool selection);
	void printLastMove(GP142_point currPos, GP142_point move);
	void switchTurn();
	~Board();
	friend void printCheck(Board& b, bool turn);
	friend class Pawn;
};

