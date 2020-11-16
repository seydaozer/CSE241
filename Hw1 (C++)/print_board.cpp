#include<iostream>
#include "nPuzzle.h"

using namespace std;

void print_board(int board[][9], int size){
	int i, j;

	for(i=0; i<size; i++){
		for(j=0; j<size; j++){
			cout.width(5);
			if(board[i][j] == 0)	cout << " ";
			else	cout << board[i][j];
		}
		cout << endl;
	}
}
