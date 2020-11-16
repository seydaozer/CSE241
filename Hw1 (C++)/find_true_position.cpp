#include<iostream>
#include "nPuzzle.h"

using namespace std;

void find_true_position(int number, int size, int& x, int& y){ // this function finds the correct coordinates in the game for a number.
	int numbers[size*size], i, j, num = 1, k = 0;

	for(i=0; i<size*size-1; i++){ // I filled the array with the numbers in the game.
		numbers[i] = num;
		num++;
	}
	numbers[size*size-1] = 0; // I put 0 on the last element of the array for the empty cell.

	for(i=0; i<size; i++){ // I found the correct coordinates for the number.
		for(j=0; j<size; j++){
			if(number == numbers[k]){
				x = i;
				y = j;
			}
			k++;
		}
	}
}
