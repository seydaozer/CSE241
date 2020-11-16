#include<iostream>
#include "nPuzzle.h"

using namespace std;

bool control_positions(int board[][9], int size){ // This function checks the numbers location.
	int numbers[size*size], i, j, number = 1, count = 0;

	for(i=0; i<size*size-1; i++){  // I filled the array with the numbers in the game.
		numbers[i] = number;
		number++;
	}
	numbers[size*size-1] = 0;  // I put 0 on the last element of the array for the empty cell.

	int n = 0;
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			if( board[i][j] !=  numbers[n] )	return false;
			n++;
		}
	}

	return true;
}
