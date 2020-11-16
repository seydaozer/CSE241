#include<iostream>
#include "nPuzzle.h"

using namespace std;

bool control_elements(int element, int k, int array[]){ // this function checks if the random number is in the board.
	int i, count = 0, flag;

	for(i=0; i<k; i++){
		if(element == array[i]) count ++;
	}

	if(count == 0)	flag = true;
	else	flag = false;

	return flag;
}
