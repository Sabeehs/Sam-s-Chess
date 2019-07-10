#include "Pawn.h"


Pawn::Pawn(int x, int y, int color) : Piece(x, y, color, "P"), enPassant(0) {}

void Pawn::draw() {
	GP142_printfP(disp, indexToMouse(position.x, position.y), 30, name.c_str());
}

void Pawn::save(ostream& out)
{
	out << 1 << " " << enPassant << " ";
	Piece::save(out);
}

void Pawn::setEnPassant(int n)
{
	enPassant = n;
}

bool Pawn::isValid(int x, int y, Board& b) {
	if (abs(x - position.x) > 2)
		return false;
	bool flag = false;
	if (b.turns % 2 == 0) {
		if (color == 0) {
			if (x == position.x + 1) {
				if (abs(y - position.y) == 1) {
					if (b.pieces[x][y] != nullptr) {
						if (b.pieces[x][y]->getColor() != this->color)
							return true;
					}
					else {
						if (isEnPassant(x, y, b))
							return true;
					}
				}
			}
			if (x == position.x + 1 && y == position.y)
				if (b.pieces[x][y] == nullptr)
					return true;

			if (moves == 0) {
				if (x == position.x + 2 && y == position.y)
					if (b.pieces[x - 1][y] == nullptr)
						if (b.pieces[x][y] == nullptr) {
							enPassant = b.turns;
							return true;
						}
			}
		}
		else {
			if (x == position.x - 1) {
				if (abs(y - position.y) == 1) {
					if (b.pieces[x][y] != nullptr) {
						if (b.pieces[x][y]->getColor() != this->color)
							return true;
					}
					else {
						if (isEnPassant(x, y, b))
							return true;
					}
				}
			}
			if (x == position.x - 1 && y == position.y)
				if (b.pieces[x][y] == nullptr)
					return true;

			if (moves == 0) {
				if (x == position.x - 2 && y == position.y)
					if (b.pieces[x + 1][y] == nullptr)
						if (b.pieces[x][y] == nullptr) {
							enPassant = b.turns;
							return true;
						}
			}
		}
	}
	else {
		if (color == 1) {
			if (x == position.x + 1) {
				if (abs(y - position.y) == 1) {
					if (b.pieces[x][y] != nullptr) {
						if (b.pieces[x][y]->getColor() != this->color)
							return true;
					}
					else {
						if (isEnPassant(x, y, b))
							return true;
					}
				}
			}
			if (x == position.x + 1 && y == position.y)
				if (b.pieces[x][y] == nullptr)
					return true;

			if (moves == 0) {
				if (x == position.x + 2 && y == position.y)
					if (b.pieces[x - 1][y] == nullptr)
						if (b.pieces[x][y] == nullptr) {
							enPassant = b.turns;
							return true;
						}
			}
		}
		else {
			if (x == position.x - 1) {
				if (abs(y - position.y) == 1) {
					if (b.pieces[x][y] != nullptr) {
						if (b.pieces[x][y]->getColor() != this->color)
							return true;
					}
					else {
						if (isEnPassant(x, y, b))
							return true;
					}
				}
			}
			if (x == position.x - 1 && y == position.y)
				if (b.pieces[x][y] == nullptr)
					return true;

			if (moves == 0) {
				if (x == position.x - 2 && y == position.y)
					if (b.pieces[x + 1][y] == nullptr)
						if (b.pieces[x][y] == nullptr) {
							enPassant = b.turns;
							return true;
						}
			}
		}
	}
	/*if (x == position.x - 1) {
		if (abs(y - position.y) == 1) {
			if (b.pieces[x][y] != nullptr) {
				if (b.pieces[x][y]->getColor() != this->color)
					return true;
			}
			else {
				if (isEnPassant(x, y, b))
					return true;
			}
		}
	}
	if (x == position.x - 1 && y == position.y)
		if (b.pieces[x][y] == nullptr)
			return true;

	if (moves == 0) {
		if (x == position.x - 2 && y == position.y)
			if (b.pieces[x + 1][y] == nullptr)
				if (b.pieces[x][y] == nullptr) {
					enPassant = b.turns;
					return true;
				}
	}
*/
	return false;
}

bool Pawn::isEnPassant(int x, int y, Board& b) {
	/*if (color == BLACK) {
		if (position.x == 4) {
			if (x == position.x + 1) {
				if (abs(y - position.y) == 1) {
					if (b.pieces[x][y] == nullptr) {
						if (b.pieces[x - 1][y] != nullptr) {
							if (b.pieces[x - 1][y]->getColor() == WHITE) {
								if (b.pieces[x - 1][y]->name == "P") {
									if (b.pieces[x - 1][y]->moves == 1) {
										Pawn* pn = dynamic_cast<Pawn*>(b.pieces[x - 1][y]);
										if (pn->enPassant == b.turns - 1) {
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	else if (color == WHITE) */{
		if (position.x == 3) {
			if (x == position.x - 1) {
				if (abs(y - position.y) == 1) {
					if (b.pieces[x][y] == nullptr) {
						if (b.pieces[x + 1][y] != nullptr) {
							if (b.pieces[x + 1][y]->getColor() != this->color) {
								if (b.pieces[x + 1][y]->name == "P") {
									if (b.pieces[x + 1][y]->moves == 1) {
										Pawn* pn = dynamic_cast<Pawn*>(b.pieces[x + 1][y]);
										if (pn->enPassant == b.turns - 1) {
											return true;
										}
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return false;
}