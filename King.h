#pragma once
#include "Piece.h"
#include "Utilities.h"
#include "Board.h"
class Board;
class Piece;
class King :
	public Piece
{
public:
	King(int x, int y, int color);
	void draw();
	void save(ostream& out);
	bool isValid(int x, int y, Board& b);
};

