#include<iostream>
#include "nPuzzle.h"

using namespace std;

int find_current_number(int number, int size){ // this function finds the number in the current block.
	int i, result;
	for(i=0; i<size*size; i++){
		if ( number == i)	result = i;
	}
	return result;
}
