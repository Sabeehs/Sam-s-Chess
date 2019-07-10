#pragma once
#include "Piece.h"
#include "Utilities.h"
#include "Board.h"
class Board;
class Piece;
class Queen :
	public Piece
{
public:
	Queen(int x, int y, int color);
	void draw();
	void save(ostream& out);
	bool isValid(int x, int y, Board& b);
};

