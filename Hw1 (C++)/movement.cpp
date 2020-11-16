#include<iostream>
#include "nPuzzle.h"

using namespace std;

void movement(int board[][9], int x1, int y1, int x2, int y2){ // this function swaps the two coordinates.
	int temp;
	temp = board[x2][y2];
	board[x2][y2] = board[x1][y1];
	board[x1][y1] = temp;
}
