#pragma once
#include "Utilities.h"
#include "Board.h"
class Board;
class Bishop :
	public Piece
{
public:
	Bishop(int x, int y, int color);
	void draw();
	void save(ostream& out);
	bool isValid(int x, int y, Board& b);
};

