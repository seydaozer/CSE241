#include<iostream>
#include "nPuzzle.h"
#include<cstdlib>

using namespace std;

int find_distance(int board[][9], int size, int empty_x,int empty_y, int block_x, int block_y){ // this function calculates the distance between the two coordinates. I also decided to move the block according to the difference between distances.
	int number, distance1, distance2, x, y;

	number = find_current_number(board[block_x][block_y], size); // this function finds the number in the current block
	find_true_position(number, size, x, y); // // this function finds the correct coordinates in the game for a number
	// I calculated the distance between the two coordinates.
	distance1 = abs(x - block_x) + abs(y - block_y);
	distance2 = abs(x - empty_x) + abs(y - empty_y);

	return distance1-distance2;	
}
