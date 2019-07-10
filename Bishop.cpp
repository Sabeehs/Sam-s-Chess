#include "Bishop.h"

Bishop::Bishop(int x, int y, int color) : Piece(x, y, color, "B") {}

void Bishop::draw() {
	GP142_printfP(disp, indexToMouse(position.x, position.y), 30, name.c_str());
}

void Bishop::save(ostream& out)
{
	out << 4 << " ";
	Piece::save(out);
}

bool Bishop::isValid(int x, int y, Board& b) {
	if (abs(x - position.x) != abs(y - position.y))
		return false;
	if (x > position.x && y > position.y) {
		for (int i = position.x + 1, j = position.y + 1; i < x && j < y; i++, j++)
			if (b.pieces[i][j] != nullptr)
				return false;
	}
	else if (x > position.x && y < position.y) {
		for (int i = position.x + 1, j = position.y - 1; i < x && j > y; i++, j--)
			if (b.pieces[i][j] != nullptr)
				return false;
	}
	else if (x < position.x && y > position.y) {
		for (int i = position.x - 1, j = position.y + 1; i > x && j < y; i--, j++)
			if (b.pieces[i][j] != nullptr)
				return false;
	}
	else {
		for (int i = position.x - 1, j = position.y - 1; i > x && j > y; i--, j--)
			if (b.pieces[i][j] != nullptr)
				return false;
	}
	if (b.pieces[x][y] != nullptr) {
		if (b.pieces[x][y]->getColor() == color)
			return false;
	}
	return true;
}