#include "Board.h"

Board::Board() : turns(0) {
	for (int i = -672, k = 0; k < 8; i += 80, k++)
		for (int j = 330, l = 0; l < 8; j -= 80, l++)
			coords[l][k] = { i,j };
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			pieces[i][j] = nullptr;
}

void Board::initialize()
{
	for (int i = 0; i < 8; i++)
		pieces[1][i] = new Pawn(1, i, BLACK);
	for (int i = 0; i < 8; i++)
		pieces[6][i] = new Pawn(6, i, WHITE);
	for (int i = 0, j = 0; i < 2; i++, j += 7) {
		pieces[j][0] = new Rook(j, 0, i);
		pieces[j][1] = new Knight(j, 1, i);
		pieces[j][2] = new Bishop(j, 2, i);
	}
	for (int i = 0, j = 0; i < 2; i++, j += 7) {
		pieces[j][7] = new Rook(j, 7, i);
		pieces[j][6] = new Knight(j, 6, i);
		pieces[j][5] = new Bishop(j, 5, i);
	}
	for (int i = 0, j = 0; i < 2; i++, j += 7) {
		pieces[j][3] = new Queen(j, 3, i);
		pieces[j][4] = new King(j, 4, i);
	}
}

void Board::printBKGND() {
	for (int i = 330; i >= -330; i--)
		draw_line(-672, i, 673, i, MED_GRAY);
}

void Board::print() {
	draw_line(-30, 330, -30, -330, MED_GRAY, 4);
	draw_line(-672, -312, -32, -312, MED_GRAY, 4);
	bool flag = true;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (flag)
				printSquare(coords[i][j], 15);
			else
				printSquare(coords[i][j], FOREST_GREEN);
			flag = !flag;
		}
		flag = !flag;
	}
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (pieces[i][j] != nullptr)
				pieces[i][j]->draw();
	int j = 0;
	for (int i = 0, k = 7; i < 2 && j < (int)wDead.size(); i++, k--) {
		for (int l = 8; j < (int)wDead.size() && l < 16; j++, l++) {
			GP142_point p = indexToMouse(k, l);
			p.x += 40, p.y -= 10;
			if (i == 1)
				p.y -= 20;
			GP142_printfP(WHITE, p, 25, wDead[j].c_str());
		}
	}
	j = 0;
	for (int i = 0, k = 0; i < 2 && j < (int)bDead.size(); i++, k++) {
		for (int l = 8; j < (int)bDead.size() && l < 16; j++, l++) {
			GP142_point p = indexToMouse(k, l);
			p.x += 40, p.y += 10;
			if (i == 1)
				p.y += 20;
			GP142_printfP(BLACK, p, 25, bDead[j].c_str());
		}
	}
}


bool Board::testTurn(int x, int y, bool turn) {
	GP142_point p = mouseToIndex(x, y);
	if (pieces[p.x][p.y] == nullptr)
		return false;
	if (turn) {
		if (pieces[p.x][p.y]->getColor() != WHITE) {
			printText("It's Player 1's Turn!");
			return false;
		}
	}
	else {
		if (pieces[p.x][p.y]->getColor() != BLACK) {
			printText("It's Player 2's Turn!");
			return false;
		}
	}
	return true;
}

bool Board::isSafe(GP142_point currPos, int x, int y) {
	Piece* temp = pieces[x][y];
	pieces[x][y] = pieces[currPos.x][currPos.y];
	pieces[x][y]->position = { x,y };
	pieces[x][y]->moves++;
	pieces[currPos.x][currPos.y] = nullptr;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (pieces[i][j]!=nullptr) {
				if (pieces[i][j]->name == "K") {
					if (pieces[i][j]->getColor() == pieces[x][y]->getColor()) {
						for (int k = 0; k < 8; k++) {
							for (int l = 0; l < 8; l++) {
								if (pieces[k][l] != nullptr) {
									if (pieces[k][l]->getColor() != pieces[x][y]->getColor()) {
										if (isClear(point(k, l), i, j)) {
											swap(pieces[x][y], pieces[currPos.x][currPos.y]);
											pieces[x][y] = temp;
											pieces[currPos.x][currPos.y]->position = { currPos.x,currPos.y };
											pieces[currPos.x][currPos.y]->moves--;
											return false;
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
	swap(pieces[x][y], pieces[currPos.x][currPos.y]);
	pieces[x][y] = temp;
	pieces[currPos.x][currPos.y]->position = { currPos.x,currPos.y };
	pieces[currPos.x][currPos.y]->moves--;
	return true;
}

bool Board::isClear(GP142_point currPos, int x, int y) {
	if (!(pieces[currPos.x][currPos.y]->isValid(x, y, *this)))
		return false;
	return true;
}

void Board::move(GP142_point currPos, int x, int y) {
	if (pieces[x][y] != nullptr) {
		if (pieces[currPos.x][currPos.y]->getColor() != pieces[x][y]->getColor()) {
			if (pieces[x][y]->color == WHITE)
				wDead.push_back(pieces[x][y]->name);
			else
				bDead.push_back(pieces[x][y]->name);
			delete pieces[x][y];
			pieces[x][y] = nullptr;
			swap(pieces[x][y], pieces[currPos.x][currPos.y]);
			pieces[x][y]->position = { x,y };
			pieces[x][y]->moves++;
			print();
			printText("Enemy Piece Captured!");
		}
		else {
			pieces[x][y]->moves++;
			pieces[currPos.x][currPos.y]->moves++;
			if (y == 0) {
				pieces[currPos.x][currPos.y]->position = { currPos.x, currPos.y - 2 };
				swap(pieces[currPos.x][currPos.y], pieces[currPos.x][currPos.y - 2]);
				pieces[x][y]->position = { x,currPos.y - 1 };
				swap(pieces[x][y], pieces[x][currPos.y - 1]);
			}
			else if (y == 7) {
				pieces[currPos.x][currPos.y]->position = { currPos.x, currPos.y + 2 };
				swap(pieces[currPos.x][currPos.y], pieces[currPos.x][currPos.y + 2]);
				pieces[x][y]->position = { x,currPos.y + 1 };
				swap(pieces[x][y], pieces[x][currPos.y + 1]);
			}
			print();
		}
	}
	else {
		swap(pieces[x][y], pieces[currPos.x][currPos.y]);
		pieces[x][y]->position = { x,y };
		pieces[x][y]->moves++;
		print();
	}
	if (pieces[x][y] != nullptr) {
		if (pieces[x][y]->name == "P") {
			bool flag = false;
			/*if (pieces[x][y]->getColor() == WHITE)*/ {
				if (pieces[x][y]->position.x == 0) {
					flag = true;
				}
				else if (x == 2) {
					if (pieces[x + 1][y] != nullptr) {
						if (pieces[x + 1][y]->getColor() != pieces[x][y]->getColor()) {
							if (pieces[x + 1][y]->name == "P") {
								if (pieces[x + 1][y]->moves == 1) {
									if (pieces[x + 1][y]->color == WHITE)
										wDead.push_back(pieces[x + 1][y]->name);
									else
										bDead.push_back(pieces[x + 1][y]->name);
									delete pieces[x + 1][y];
									pieces[x + 1][y] = nullptr;
									print();
									printText("Enemy Piece Captured!");
								}
							}
						}
					}
				}
			}
			/*else if (pieces[x][y]->getColor() == BLACK) {
				if (pieces[x][y]->position.x == 7) {
					flag = true;
				}
				else if (x == 5) {
					if (pieces[x - 1][y] != nullptr) {
						if (pieces[x - 1][y]->getColor() == WHITE) {
							if (pieces[x - 1][y]->name == "P") {
								if (pieces[x - 1][y]->moves == 1) {
									delete pieces[x - 1][y];
									pieces[x - 1][y] = nullptr;
									print();
									printText("Enemy Piece Captured!");
								}
							}
						}
					}
				}
			}*/
			if (flag) {
				printBKGND();
				print();
				printText("PAWN PROMOTION:\n\nPress R for Rook\nPress N for Knight\nPress B for Bishop\nPress Q for Queen");
				int m1, m2;
				char c = 'a';
				bool loop = true;
				while (loop) {
					GP142_await_event(&m1, &m2, &c);
					if (c == 'r' || c == 'R' || c == 'n' || c == 'N' || c == 'b' || c == 'B' || c == 'q' || c == 'Q') {
						Piece* temp = pieces[x][y];
						if (c == 'r' || c == 'R') {
							pieces[x][y] = new Rook(temp->position.x, temp->position.y, temp->color);
							pieces[x][y]->moves = temp->moves;
							pieces[x][y]->position = temp->position;
						}
						else if (c == 'n' || c == 'N') {
							pieces[x][y] = new Knight(temp->position.x, temp->position.y, temp->color);
							pieces[x][y]->moves = temp->moves;
							pieces[x][y]->position = temp->position;
						}
						else if (c == 'b' || c == 'B') {
							pieces[x][y] = new Bishop(temp->position.x, temp->position.y, temp->color);
							pieces[x][y]->moves = temp->moves;
							pieces[x][y]->position = temp->position;
						}
						else {
							pieces[x][y] = new Queen(temp->position.x, temp->position.y, temp->color);
							pieces[x][y]->moves = temp->moves;
							pieces[x][y]->position = temp->position;
						}
						printBKGND();
						loop = false;
					}
				}
			}
		}
	}
	turns++;
}

bool Board::isCheck(bool turn) {
	int color;
	if (turn)
		color = BLACK;
	else
		color = WHITE;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (pieces[i][j] != nullptr) {
				if (pieces[i][j]->name == "K") {
					if (pieces[i][j]->getColor() == color) {
						for (int k = 0; k < 8; k++) {
							for (int l = 0; l < 8; l++) {
								if (pieces[k][l] != nullptr) {
									if (pieces[k][l]->getColor() != color) {
										if (isClear(point(k, l), i, j)) {
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

bool Board::isCheckMate(bool turn) {
	int color;
	if (turn)
		color = BLACK;
	else
		color = WHITE;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (pieces[i][j] != nullptr) {
				if (pieces[i][j]->getColor() == color) {
					for (int k = 0; k < 8; k++) {
						for (int l = 0; l < 8; l++) {
							if (i != k || j != l) {
								if (isClear(point(i, j), k, l)) {
									if (isSafe(point(i, j), k, l)) {
										return false;
									}
								}
							}
						}
					}
				}
			}
		}
	}
	return true;
}

bool Board::isDraw() {
	int count = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (pieces[i][j] != nullptr)
				++count;
	if (count == 2)
		return true;
	if (count == 3) 
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (pieces[i][j] != nullptr)
					if (pieces[i][j]->name == "N" || pieces[i][j]->name == "B")
						return true;
	if (count == 4) {
		int knights = 0, bishops = 0;
		for (int i = 0; i < 8; i++)
			for (int j = 0; j < 8; j++)
				if (pieces[i][j] != nullptr) {
					if (pieces[i][j]->name == "N")
						knights++;
					else if (pieces[i][j]->name == "B")
						bishops++;
				}
		if (knights == 2)
			return true;
		if (bishops == 2) {
			int clr = -1;
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					if (pieces[i][j] != nullptr)
						if (pieces[i][j]->name == "B") {
							clr = pieces[i][j]->color;
							for (int k = i; k < 8; k++)
								for (int l = j + 1; l < 8; l++)
									if (pieces[k][l] != nullptr)
										if (pieces[k][l]->name == "B")
											if (pieces[k][l]->color != clr)
												return true;
						}
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					if (pieces[i][j] != nullptr)
						if (pieces[i][j]->name == "B") {
							int ith = i % 2, jth = j % 2;
							for (int k = i; k < 8; k++)
								for (int l = j + 1; l < 8; l++)
									if (pieces[k][l] != nullptr)
										if (pieces[k][l]->name == "B") {
											if (ith == jth) {
												if (k == l)
													return true;
											}
											else {
												if (k != l)
													return true;
											}
										}
						}
		}
		if (knights == 1 && bishops == 1) {
			int clr = -1;
			for (int i = 0; i < 8; i++)
				for (int j = 0; j < 8; j++)
					if (pieces[i][j] != nullptr)
						if (pieces[i][j]->name == "B") {
							clr = pieces[i][j]->color;
							for (int k = 0; k < 8; k++)
								for (int l = 0; l < 8; l++)
									if (pieces[k][l] != nullptr)
										if (pieces[k][l]->name == "N")
											if (pieces[k][l]->color != clr)
												return true;
						}
		}
	}
	return false;
}

void Board::printMoves(GP142_point p, bool selection) {
	if (p.x == -1 || p.y == -1)
		return;
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (i != p.x || j != p.y) {
				if (isClear(p, i, j)) {
					if (isSafe(p, i, j)) {
						if (pieces[i][j] != nullptr && (pieces[i][j]->getColor() != pieces[p.x][p.y]->getColor()))
							printSelection(point(i, j), *this, selection, RED);
						else {
							if (pieces[p.x][p.y]->name == "P") {
								Pawn* temp = dynamic_cast<Pawn*>(pieces[p.x][p.y]);
								if (temp->isEnPassant(i, j, *this))
									printSelection(point(i, j), *this, selection, RED);
								else
									printSelection(point(i, j), *this, selection, BLUE);
							}
							else
								printSelection(point(i, j), *this, selection, BLUE);
						}
					}
				}
			}
		}
	}
}

void Board::printLastMove(GP142_point currPos, GP142_point move)
{
	if (currPos.x != -1 && currPos.y != -1) {
		currPos.x = 7 - currPos.x, currPos.y = 7 - currPos.y;
		move.x = 7 - move.x, move.y = 7 - move.y;
		printSelection(currPos, *this, 1, 22);
		printSelection(move, *this, 1, 22);
		//printSquare(coords[abs(currPos.x)][abs(currPos.y)], GREEN, 30);
		//printSquare(coords[abs(move.x)][abs(move.y)], GREEN, 30);
		if (pieces[abs(currPos.x)][abs(currPos.y)] != nullptr)
			pieces[abs(currPos.x)][abs(currPos.y)]->draw();
		if (pieces[abs(move.x)][abs(move.y)] != nullptr)
			pieces[abs(move.x)][abs(move.y)]->draw();
	}
}

void Board::switchTurn() {
	for (int i = 0, k = 7; i < 4; i++, k--) {
		for (int j = 0, l = 7; j < 8; j++, l--) {
			swap(pieces[i][j], pieces[k][l]);
			if (pieces[i][j] != nullptr)
				pieces[i][j]->position = { i,j };
			if (pieces[k][l] != nullptr)
				pieces[k][l]->position = { k,l };
		}
	}
}

Board::~Board()
{
	for (int i = 0; i < 8; i++) {
		for (int j = 0; j < 8; j++) {
			if (pieces[i][j] != nullptr) {
				delete pieces[i][j];
			}
		}
	}
}
