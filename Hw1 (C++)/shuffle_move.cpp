#include<iostream>
#include "nPuzzle.h"
#include<ctime>
#include<cstdlib>

using namespace std;

void shuffle_move(int board[][9], int size){
	int numbers[size*size], i, j, number = 1, k = 0;

	for(i=0; i<size*size-1; i++){ // I filled the array with the numbers in the game.
		numbers[i] = number;
		number++;
	}
	numbers[size*size-1] = 0; // I put 0 on the last element of the array for the empty cell.

	for(i=0; i<size; i++){ // I filled the board with the numbers in the array(numbers).
		for(j=0; j<size; j++){
			board[i][j] = numbers[k];
			k++;
		}
	}
	cout << "The final board is:" << endl;
	print_board(board, size);

	int random_move, x, y, flag /*this variable checks whether moves are made*/;
	k = 0;
	while(k < size*size){
		find_empty_cell(board, size, x, y);
		random_move = rand() % 4; // for Left, Right, Up, Down
		switch(random_move){
			case 0: //LEFT
				if(y > 0){
					movement(board, x, y, x, y-1);
					flag = 1;
				}
				else	flag = 0;
			break;
			case 1: //RIGHT
				if(y < size-1){
					movement(board, x, y, x, y+1);	
					flag = 1;
				}
				else	flag = 0;
			break;
			case 2: //UP
				if(x > 0){
					movement(board, x, y, x-1, y);	
					flag = 1;
				}
				else	flag = 0;
			break;
			case 3: //DOWN
				if(x < size-1){
					movement(board, x, y, x+1, y);
					flag = 1;
				}
				else	flag = 0;
			break;
		}
		if(flag == 1){ 
			k++; // The counter increases if move is made.(if the flag equals one)
			cout << endl << k << ". random move is:";
			if(random_move == 0)	cout << " L" << endl;
			else if(random_move == 1) cout << " R" << endl;
			else if(random_move == 2) cout << " U" << endl;
			else if(random_move == 3) cout << " D" << endl;
			print_board(board, size);
		}
	}
}
