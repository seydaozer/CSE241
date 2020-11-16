#include<iostream>
#include "nPuzzle.h"
#include<cstdlib>

using namespace std;

void four_locate_move(int board[][9], int size, int empty_x, int empty_y, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){ // this function is for blocks with four blocks around it. (for middle sections)
	int distance1, distance2, distance3, distance4;
	
	distance1 = find_distance(board, size, empty_x, empty_y, x1, y1);
	distance2 = find_distance(board, size, empty_x, empty_y, x2, y2);
	distance3 = find_distance(board, size, empty_x, empty_y, x3, y3);
	distance4 = find_distance(board, size, empty_x, empty_y, x4, y4);
	// If all number are positive, the smaller one moves.		
	if(distance1 >= 0){  // distance1 positive
		if(distance2 >= 0){ // distance2 positive (distance1 positive)
			if(distance3 >= 0){ // distance3 positive (distance1 , distance2 positive)
				if(distance4 >= 0){ // distance4 positive (1, 2, 3, 4 positive)
					if(distance1 <= distance2 && distance1 <= distance3 && distance1 <= distance4) movement(board, x1, y1, empty_x, empty_y);
					else if(distance2 <= distance1 && distance2 <= distance3 && distance2 <= distance4) movement(board, x2, y2, empty_x, empty_y);
					else if(distance3 <= distance1 && distance3 <= distance2 && distance3 <= distance4)	movement(board, x3, y3, empty_x, empty_y);
					else if(distance4 <= distance1 && distance4 <= distance2 && distance4 <= distance3)	movement(board, x4, y4, empty_x, empty_y);
				}
				else{ // distance4 negative (1, 2, 3 positive)
					if(distance1 <= distance2 && distance1 <= distance3) movement(board, x1, y1, empty_x, empty_y);
					else if(distance2 <= distance1 && distance2 <= distance3) movement(board, x2, y2, empty_x, empty_y);
					else if(distance3 <= distance1 && distance3 <= distance2)	movement(board, x3, y3, empty_x, empty_y);
				}
			}
			else{ // distance3 negative (distance1 , distance2 positive)
				if(distance4 >= 0){ // distance4 positive (1, 2, 4 positive)
					if(distance1 <= distance2 && distance1 <= distance4) movement(board, x1, y1, empty_x, empty_y);
					else if(distance2 <= distance1 && distance2 <= distance4) movement(board, x2, y2, empty_x, empty_y);
					else if(distance4 <= distance1 && distance4 <= distance2)	movement(board, x4, y4, empty_x, empty_y);
				}
				else{ // distance4 negative (1, 2 positive)
					if(distance1 < distance2) movement(board, x1, y1, empty_x, empty_y);
					else	movement(board, x2, y2, empty_x, empty_y);
				}
			}
		}
		else{ // distance2 negative
			if(distance3 >= 0){ // distance3 positive (distance1 positive, distance2 negative)
				if(distance4 >= 0){ // distance4 positive (1, 3, 4 positive)
					if(distance1 <= distance3 && distance1 <= distance4) movement(board, x1, y1, empty_x, empty_y);
					else if(distance3 <= distance1 && distance3 <= distance4) movement(board, x3, y3, empty_x, empty_y);
					else if(distance4 <= distance1 && distance4 <= distance3)	movement(board, x4, y4, empty_x, empty_y);
				}
				else{// distance4 negative (1, 3 positive)
					if(distance1 < distance3) movement(board, x1, y1, empty_x, empty_y);
					else	movement(board, x3, y3, empty_x, empty_y);
				}
			}
			else{ // distance3 negative (distance1 positive, distance2 negative)
				if(distance4 >= 0){ // distance4 positive (1, 4 positive)
					if(distance1 < distance4) movement(board, x1, y1, empty_x, empty_y);
					else	movement(board, x4, y4, empty_x, empty_y);
				}
				else // distance4 negative ( 1 positive)
					movement(board, x1, y1, empty_x, empty_y);
			}
		}
	}
	else{ // distance1 < 0
		if(distance2 >= 0){ // distance2 negative
			if(distance3 >= 0){ // distance3 positive (distance1 negative, distance2 positive)
				if(distance4 >= 0){ // (2, 3, 4 positive)
					if(distance2 <= distance3 && distance2 <= distance4) movement(board, x2, y2, empty_x, empty_y);
					else if(distance3 <= distance2 && distance3 <= distance4) movement(board, x3, y3, empty_x, empty_y);
					else if(distance4 <= distance2 && distance4 <= distance3)	movement(board, x4, y4, empty_x, empty_y);
				}
				else{ // distance4 negative (2, 3 positive)
					if(distance2 < distance3) movement(board, x2, y2, empty_x, empty_y);
					else	movement(board, x3, y3, empty_x, empty_y);

				}
			}
			else{ // distance3 negative (distance1 negative, distance2 positive)
				if(distance4 >= 0){ // (2, 4 positive)
					if(distance2 < distance4) movement(board, x2, y2, empty_x, empty_y);
					else	movement(board, x4, y4, empty_x, empty_y);
				}
				else // distance4 negative (2 positive)
					movement(board, x2, y2, empty_x, empty_y);
			}
		}
		else{ // distance2 negative
			if(distance3 >= 0){ // distance3 positive (distance1, distance2 negative)
				if(distance4 >= 0){ // (3, 4 positive)
					if(distance3 < distance4) movement(board, x3, y3, empty_x, empty_y);
					else	movement(board, x4, y4, empty_x, empty_y);
				}
				else // distance4 negative (3 positive)
					movement(board, x3, y3, empty_x, empty_y);
			}
			else{ // distance3 negative (distance1, distance2 negative)
				if(distance4 >= 0) // (4 positive)
					movement(board, x4, y4, empty_x, empty_y);
				else{ // distance4 negative (1, 2, 3, 4 negative)
				// distance1, distance2 and distance3 are negative numbers(if the distance is negative, the number moves away from the corrrect position.), so I found the positive values for them and I chose to move the big one.
					distance1 = abs(distance1);
					distance2 = abs(distance2);
					distance3 = abs(distance3);
					distance4 = abs(distance4);

					if(distance1 >= distance2 && distance1 >= distance3 && distance1 >= distance4) movement(board, x1, y1, empty_x, empty_y);
					else if(distance2 >= distance1 && distance2 >= distance3 && distance2 >= distance4) movement(board, x2, y2, empty_x, empty_y);
					else if(distance3 >= distance1 && distance3 >= distance2 && distance3 >= distance4)	movement(board, x3, y3, empty_x, empty_y);
					else if(distance4 >= distance1 && distance4 >= distance2 && distance4 >= distance3)	movement(board, x4, y4, empty_x, empty_y);
				}
			}
		}
	}
}

