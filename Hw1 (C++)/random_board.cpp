#include<iostream>
#include<ctime>
#include<cstdlib>
#include "nPuzzle.h"

using namespace std;

void random_board(int board[][9], int size){
	int control_array[size*size], k = 0, i, j;
	bool flag;
	//fill the board
	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			do{
				board[i][j] = rand() % (size*size);
				flag = control_elements(board[i][j], k, control_array); // this function checks if the random number is in the board.
			}while(flag != true);
			control_array[k] = board[i][j];
			k++;
		}
	}
}
