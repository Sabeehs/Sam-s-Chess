#include "Piece.h"

Piece::Piece(int x, int y, int c, string n) : position({ x,y }), name(n), color(c), moves(0) {
	if (color == BLACK)
		disp = 0;
	else
		disp = 1;
}

void Piece::save(ostream& out) {
	out << position.x << " " << position.y << " " << color << " " << moves << endl;
}

int Piece::getColor() {
	return color;
}


