#include "Rook.h"

Rook::Rook(int x, int y, int color) : Piece(x, y, color, "R") {}

void Rook::draw() {
	GP142_printfP(disp, indexToMouse(position.x, position.y), 30, name.c_str());
}

void Rook::save(ostream& out)
{
	out << 2 << " ";
	Piece::save(out);
}

bool Rook::isValid(int x, int y, Board& b) {
	if (x != position.x && y != position.y)
		return false;
	if (x == position.x && y > position.y) {
		for (int i = position.y + 1; i < y; i++)
			if (b.pieces[x][i] != nullptr)
				return false;
	}
	else if (x == position.x && y < position.y) {
		for (int i = position.y - 1; i > y; i--)
			if (b.pieces[x][i] != nullptr)
				return false;
	}
	else if (x < position.x && y == position.y) {
		for (int i = position.x - 1; i > x; i--)
			if (b.pieces[i][y] != nullptr)
				return false;
	}
	else {
		for (int i = position.x + 1; i < x; i++)
			if (b.pieces[i][y] != nullptr)
				return false;
	}
	if (b.pieces[x][y] != nullptr) {
		if (b.pieces[x][y]->getColor() == color)
			return false;
	}
	return true;
}