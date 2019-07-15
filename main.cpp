#include <iostream>
#include <fstream>
#include "GP142.h"
#include <stdio.h>
#include <math.h>
#include "Utilities.h"
#include "Board.h"

#define PI 3.1415926535
#define ANIMATE_MSG "Select \"Animate\"\nOn the \"Run\" Menu"
#define TEXT_SIZE 20
using namespace std;



//Mouse handler
void handle_mouse(int x, int y) {
	GP142_printfXY(BLACK, x, y, 9, "(%d,%d)", x, y);
}

//Keyboard handler
void handle_kbd(char c)
{
	GP142_printfXY(BLACK, 0, 0, TEXT_SIZE, "%c", c);
}

void demo_handle_periodic(void) {};


int main() {
	GP142_open();
	int choice = getChoice();
	if (choice == 2)
		return 0;
	int quit = 0;
	int mouse_x = 0, mouse_y = 0;
	char key_pressed;
	Board b;
	bool turn = true;
	bool check = false;
	if (choice == 1)
		loadGame(b, turn, check);
	else
		b.initialize();
	b.printBKGND();
	b.print();
	bool selection = false;
	int clicks = 0;
	GP142_point currPos = { -1,-1 }, moveFrom = { -1,-1 }, moveTo = { -1,-1 },
		temp = { -1,-1 }, m1 = { -1,-1 }, m2 = { -1,-1 };
	//The Event Loop  
	while (!quit) {
		saveGame(b, turn, check);
		if (check) {
			GP142_printfXY(BLACK, 200, -110, 30, "CHECK!");
			printCheck(b, turn);
		}
		if (turn)
			GP142_printfXY(BLACK, 200, 100, 20, "Player 1's Turn");
		else
			GP142_printfXY(BLACK, 200, 100, 20, "Player 2's Turn");
		switch (GP142_await_event(&mouse_x, &mouse_y, &key_pressed)) {
		case GP142_QUIT:
			quit = 1;
			break;

		case GP142_MOUSE:
			b.printBKGND();
			/*b.print();
			printSelection(currPos, b, selection, BLUE);
			b.printMoves(currPos, selection);*/
			if (mouse_x < -32 && mouse_y > -310) {
				if (clicks == 0) {
					if (b.testTurn(mouse_x, mouse_y, turn))
					{
						selection = true;
						currPos = mouseToIndex(mouse_x, mouse_y);
						clicks++;
					}
				}
				else if (clicks == 1) {
					if ((mouseToIndex(mouse_x, mouse_y).x != currPos.x || mouseToIndex(mouse_x, mouse_y).y != currPos.y)) {
						temp = mouseToIndex(mouse_x, mouse_y);
						if (b.pieces[abs(temp.x)][abs(temp.y)] == nullptr || 
							(b.pieces[abs(temp.x)][abs(temp.y)]->getColor() != b.pieces[abs(currPos.x)][abs(currPos.y)]->getColor())
							|| ((currPos.x==7 && (currPos.y==3 || currPos.y==4)) && (temp.x==7 && (temp.y == 0 || temp.y == 7)))) {
							if (b.isClear(currPos, temp.x, temp.y)) {
								if (b.isSafe(currPos, temp.x, temp.y)) {
									b.move(currPos, temp.x, temp.y);
									b.switchTurn();
									m1 = currPos, m2 = temp;
									check = b.isCheck(turn);
									if (b.isCheckMate(turn)) {
										b.printBKGND();
										b.print();
										if (check) {
											
											printText("Check Mate!");
											printCheck(b, !turn);
											if (turn)
												printText("\n\nBLUE WINS!");
											else
												printText("\n\nRED WINS!");
										}
										else
											printText("Stale Mate!\n\nGAME DRAW!");
										GP142_flush();
										quit = 1;
										GP142_await_event(&mouse_x, &mouse_y, &key_pressed);
										break;
									}
									else if (b.isDraw()) {
										b.printBKGND();
										b.print();
										printText("GAME DRAWN!\n\nNobody Wins");
										GP142_flush();
										quit = 1;
										GP142_await_event(&mouse_x, &mouse_y, &key_pressed);
										break;
									}
									clicks++;
									turn = !turn;
									selection = false;
									currPos = { -1,-1 };
								}
								else
									printText("Can't Put Your King In Danger");
							}
							else
								printText("Invalid Move");
						}
						else {
							currPos = mouseToIndex(mouse_x, mouse_y);
						}
					}
					else {
						selection = false;
						currPos = { -1,-1 };
						clicks = 0;
					}
				}
			}
			else {
				if (clicks == 0)
					printText("Please Click Inside the Board");
				else if (clicks == 1) {
					selection = false;
					currPos = { -1,-1 };
					clicks = 0;
				}
			}
			if (clicks == 2) {
				clicks = 0;
			}
			//b.printBKGND();
			b.print();
			b.printLastMove(m1, m2);
			printSelection(currPos, b, selection, BLUE);
			b.printMoves(currPos, selection);
			break;

		default:
			break;
		}
	}
	GP142_close();
	return 0;
}