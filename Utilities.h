#pragma once
#include "GP142.H"
#include "Board.h"
#include <string>
#include <fstream>
using namespace std;
class Board;

void draw_line(int x1, int y1, int x2, int y2, int color = BLACK, int width = 1);
GP142_point point(int x, int y);
GP142_point mouseToIndex(int x, int y);
GP142_point indexToMouse(int x, int y);
void printText(string s);
void drawRectangle(int a, int b, int x, int y, int c = WHITE, int t = 1);
int getChoice();
void saveGame(Board& b, bool turn, bool check);
void loadGame(Board& b, bool& turn, bool& check);
void printSquare(GP142_point p, int color, int ind = 0);
void printSelection(GP142_point p, Board& b, bool s, int color);
void printCheck(Board& b, bool turn);