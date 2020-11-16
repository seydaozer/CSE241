#include<iostream>
#include "nPuzzle.h"
#include<cstdlib>

using namespace std;

void two_locate_move(int board[][9], int size, int empty_x, int empty_y, int x1, int y1, int x2, int y2){ // this function is for blocks with two blocks around it. (for corners)
	int distance1, distance2;

	distance1 = find_distance(board, size, empty_x, empty_y, x1, y1);
	distance2 = find_distance(board, size, empty_x, empty_y, x2, y2);
	// If all number are positive, the smaller one moves.	
	if(distance1 > 0 && distance2 < 0)	movement(board, x1, y1, empty_x, empty_y);
	else if(distance1 < 0 && distance2 > 0)	movement(board, x2, y2, empty_x, empty_y);
	else{ // distance1 and distance2 are negative numbers(if the distance is negative, the number moves away from the corrrect position.), so I found the positive values for them and I chose to move the big one.
		distance1 = abs(distance1);
		distance2 = abs(distance2);

		if(distance1 > distance2) movement(board, x1, y1, empty_x, empty_y);
		else	movement(board, x2, y2, empty_x, empty_y);
	}
}
