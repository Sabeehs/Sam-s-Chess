#include "Piece.h"
#include "Knight.h"

Knight::Knight(int x, int y, int color) : Piece(x, y, color, "N") {}

void Knight::draw() {
	GP142_printfP(disp, indexToMouse(position.x, position.y), 30, name.c_str());
}

void Knight::save(ostream& out)
{
	out << 3 << " ";
	Piece::save(out);
}

bool Knight::isValid(int x, int y, Board& b) {
	if ((abs(x - position.x) == 2 && abs(y - position.y) == 1) || (abs(x - position.x) == 1 && abs(y - position.y) == 2)) {
		if (b.pieces[x][y] != nullptr) {
			if (b.pieces[x][y]->getColor() != color)
				return true;
		}
		else
			return true;
	}
	return false;
}