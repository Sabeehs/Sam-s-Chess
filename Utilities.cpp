#include "Utilities.h"

void draw_line(int x1, int y1, int x2, int y2, int color, int width) {
	GP142_lineXY(color, x1, y1, x2, y2, width);
}

GP142_point point(int x, int y) {
	GP142_point p = { x, y };
	return p;
}

GP142_point mouseToIndex(int x, int y) {
	GP142_point p = { (int)abs((y - 330)) / 80 , (x + 672) / 80 };
	return p;
}

GP142_point indexToMouse(int x, int y) {
	GP142_point p = { -642 + (y * 80), 272 - (x * 80) };
	return p;
}

void printText(string s) {
	GP142_printfXY(BLACK, 200, 0, 20, s.c_str());
}

void drawRectangle(int a, int b, int x, int y, int c, int t) {
	draw_line(a, b, x, b, c, t);
	draw_line(x, b, x, y, c, t);
	if (t == 2)
		++b;
	draw_line(a, b, a, y, c, t);
	if (t == 1)
		++x;
	draw_line(a, y, x, y, c, t);
}

int getChoice() {
	drawRectangle(-160, 200, 160, 120, 1, 2);
	GP142_printfXY(9, -50, 135, 45, "New");
	drawRectangle(-160, 40, 160, -40, 1, 2);
	GP142_printfXY(9, -55, -25, 45, "Load");
	drawRectangle(-160, -120, 160, -200, 1, 2);
	GP142_printfXY(9, -45, -185, 45, "Exit");
	int mouse_x, mouse_y;
	char key_pressed;
	while (true) {
		GP142_await_event(&mouse_x, &mouse_y, &key_pressed);
		if (key_pressed == '\0') {
			if (mouse_x > -160 && mouse_x < 160 && mouse_y > 120 && mouse_y < 200)
				return 0;
			else if (mouse_x > -160 && mouse_x < 160 && mouse_y > -40 && mouse_y < 40)
				return 1;
			else if (mouse_x > -160 && mouse_x < 160 && mouse_y > -200 && mouse_y < -120)
				return 2;
		}
	}
	return 0;
}

void saveGame(Board& b, bool turn, bool check)
{
	int count = 0;
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (b.pieces[i][j] != nullptr)
				++count;
	ofstream out;
	out.open("ChessSave.dat");
	out << turn << " " << check << "\n";
	out << count << "\n";
	for (int i = 0; i < 8; i++)
		for (int j = 0; j < 8; j++)
			if (b.pieces[i][j] != nullptr)
				b.pieces[i][j]->save(out);
	out << b.turns;
	out.close();
	out.open("Dead.dat");
	out << b.wDead.size() << "\n";
	for (int i = 0; i < (int)b.wDead.size(); i++)
		out << b.wDead[i] << "\n";
	out << b.bDead.size() << "\n";
	for (int i = 0; i < (int)b.bDead.size(); i++)
		out << b.bDead[i] << "\n";
	out.close();
}

void loadGame(Board& b, bool& turn, bool& check)
{
	ifstream in;
	in.open("ChessSave.dat");
	int n, m, x, y, c, count = 0;
	string s;
	in >> turn >> check;
	in >> count;
	for (int i = 0; i < count; i++) {
		in >> n;
		if (n == 1) {
			int enp;
			in >> enp;
			in >> x >> y >> c >> m;
			b.pieces[x][y] = new Pawn(x, y, c);
			b.pieces[x][y]->moves = m;
			Pawn* pawn = dynamic_cast<Pawn*>(b.pieces[x][y]);
			pawn->setEnPassant(enp);
		}
		else if (n == 2) {
			in >> x >> y >> c >> m;
			b.pieces[x][y] = new Rook(x, y, c);
			b.pieces[x][y]->moves = m;
		}
		else if (n == 3) {
			in >> x >> y >> c >> m;
			b.pieces[x][y] = new Knight(x, y, c);
			b.pieces[x][y]->moves = m;
		}
		else if (n == 4) {
			in >> x >> y >> c >> m;
			b.pieces[x][y] = new Bishop(x, y, c);
			b.pieces[x][y]->moves = m;
		}
		else if (n == 5) {
			in >> x >> y >> c >> m;
			b.pieces[x][y] = new Queen(x, y, c);
			b.pieces[x][y]->moves = m;
		}
		else if (n == 6) {
			in >> x >> y >> c >> m;
			b.pieces[x][y] = new King(x, y, c);
			b.pieces[x][y]->moves = m;
		}
	}
	in >> b.turns;
	in.close();
	in.open("Dead.dat");
	in >> count;
	for (int i = 0; i < count; i++) {
		in >> s;
		b.wDead.push_back(s);
	}
	in >> count;
	for (int i = 0; i < count; i++) {
		in >> s;
		b.bDead.push_back(s);
	}
	in.close();
}

void printSquare(GP142_point p, int color, int ind) {
	for (int i = 0; i < 80 - (ind*2); i++) {
		draw_line(p.x +ind, p.y -ind, p.x + 80 -ind, p.y -ind, color);
		--p.y;
	}
}

void printSelection(GP142_point p, Board& b, bool s, int color) {
	if (s) {
		int i = 4;
		GP142_point q = p;
		p = b.coords[p.x][p.y];
		/*printSquare(p, GREEN);
		GP142_point q = mouseToIndex(p.x, p.y);
		if (b.pieces[q.x][q.y] != nullptr)
			b.pieces[q.x][q.y]->draw();*/
		if (q.x % 2 != q.y % 2)
			drawRectangle(p.x + i +1, p.y - i -1, p.x + 80 - i -1, p.y - 80 + i+1, color, 6);
		else
			drawRectangle(p.x + i, p.y - i, p.x + 80 - i, p.y - 80 + i, color, 6);
	}
}

void printCheck(Board& b, bool turn) {
	if (turn) {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (b.pieces[i][j] != nullptr) {
					if (b.pieces[i][j]->name == "K") {
						if (b.pieces[i][j]->getColor() == WHITE) {
							printSquare(b.coords[i][j], RED, 6);
							b.pieces[i][j]->draw();
							return;
						}
					}
				}
			}
		}
	}
	else {
		for (int i = 0; i < 8; i++) {
			for (int j = 0; j < 8; j++) {
				if (b.pieces[i][j] != nullptr) {
					if (b.pieces[i][j]->name == "K") {
						if (b.pieces[i][j]->getColor() == BLACK) {
							printSquare(b.coords[i][j], RED, 6);
							b.pieces[i][j]->draw();
							return;
						}
					}
				}
			}
		}
	}
}

