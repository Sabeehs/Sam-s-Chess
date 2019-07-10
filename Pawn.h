#pragma once
#include "Piece.h"
#include "Utilities.h"
#include "Board.h"
class Board;
class Piece;
class Pawn :
	public Piece
{
	int enPassant;
public:
	Pawn(int x, int y, int color);
	void draw();
	void save(ostream& out);

	void setEnPassant(int n);
	bool isValid(int x, int y, Board& b);
	bool isEnPassant(int x, int y, Board& b);
	friend void loadGame(Board& b, bool& turn, bool& check);
};

