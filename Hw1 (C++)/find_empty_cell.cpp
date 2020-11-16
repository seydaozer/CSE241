#include<iostream>
#include "nPuzzle.h"

using namespace std;

void find_empty_cell(int board[][9], int size, int& x, int& y){ // this function finds the empty cell's coordinates.
	int i, j;

	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			if(board[i][j] == 0){
				x = i;
				y = j;
			}
		}
	}
}
