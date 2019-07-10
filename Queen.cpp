#include "Queen.h"

Queen::Queen(int x, int y, int color) : Piece(x, y, color, "Q") {}

void Queen::draw() {
	GP142_printfP(disp, indexToMouse(position.x, position.y), 30, name.c_str());
}

void Queen::save(ostream& out)
{
	out << 5 << " ";
	Piece::save(out);
}

bool Queen::isValid(int x, int y, Board& b) {
	if (b.pieces[x][y] != nullptr) {
		if (b.pieces[x][y]->getColor() == color)
			return false;
	}
	if (abs(x - position.x) == abs(y - position.y)) {
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
		else if (x < position.x&& y < position.y) {
			for (int i = position.x - 1, j = position.y - 1; i > x && j > y; i--, j--)
				if (b.pieces[i][j] != nullptr)
					return false;
		}
		return true;
	}
	if (x == position.x || y == position.y) {
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
		else if (x < position.x&& y == position.y) {
			for (int i = position.x - 1; i > x; i--)
				if (b.pieces[i][y] != nullptr)
					return false;
		}
		else if (x > position.x && y == position.y) {
			for (int i = position.x + 1; i < x; i++)
				if (b.pieces[i][y] != nullptr)
					return false;
		}
		return true;
	}
	return false;
}