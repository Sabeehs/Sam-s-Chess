#include "King.h"

King::King(int x, int y, int color) : Piece(x, y, color, "K") {}

void King::draw() {
	GP142_printfP(disp, indexToMouse(position.x, position.y), 30, name.c_str());
}

void King::save(ostream& out)
{
	out << 6 << " ";
	Piece::save(out);
}

bool King::isValid(int x, int y, Board& b) {
	if (b.pieces[x][y] != nullptr) {
		if (b.pieces[x][y]->getColor() == color) {
			if (b.pieces[x][y]->name == "R") {
				if (moves == 0 && b.pieces[x][y]->moves == 0) {
					bool flag = true, test = false;
					if (color == 0)
						test = true;
					if (b.isCheck(test))
						flag = false;
					if (y == 0) {
						if (color == 0) {
							for (int i = 1; i < 3; i++) {
								if (b.pieces[x][i] != nullptr || (!b.isSafe(position, x, i)))
									flag = false;
							}
						}
						else {
							for (int i = 1; i < 4; i++) {
								if (b.pieces[x][i] != nullptr || ((!b.isSafe(position, x, i) && i > 1)))
									flag = false;
							}
						}
					}
					else if (y == 7) {
						if (color == 0) {
							for (int i = 4; i < 7; i++) {
								if (b.pieces[x][i] != nullptr || ((!b.isSafe(position, x, i) && i < 6)))
									flag = false;
							}
						}
						else {
							for (int i = 5; i < 7; i++) {
								if (b.pieces[x][i] != nullptr || (!b.isSafe(position, x, i)))
									flag = false;
							}
						}
					}
					if (flag)
						return true;
				}
			}
		}
	}
	if (abs(x - position.x) > 1 || abs(y - position.y) > 1)
		return false;
	if (b.pieces[x][y] != nullptr) {
		if (b.pieces[x][y]->getColor() == color)
			return false;
	}
	return true;
}