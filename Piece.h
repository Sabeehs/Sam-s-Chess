#pragma once
#include "GP142.H"
#include <iostream>
#include <string>
using namespace std;
class Board;
class Piece
{
protected:
		GP142_point position;
		string name;
		int color;
		int disp;
		int moves;
	public:
		Piece(int x, int y, int c, string n);
		virtual void draw() = 0 {}
		virtual bool isValid(int x, int y, Board& b) = 0{}
		virtual void save(ostream& out);
		virtual int getColor();
		


		friend class Board;
		friend class Pawn;
		friend class King;
		friend void printCheck(Board& b, bool turn);
		friend void loadGame(Board& b, bool& turn, bool& check);
};

