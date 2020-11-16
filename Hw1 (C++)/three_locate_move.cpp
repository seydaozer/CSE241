#include<iostream>
#include "nPuzzle.h"
#include<cstdlib>

using namespace std;

void three_locate_move(int board[][9], int size, int empty_x, int empty_y, int x1, int y1, int x2, int y2, int x3, int y3){ // this function is for blocks with three blocks around it. (for edges)
	int distance1, distance2, distance3;
	
	distance1 = find_distance(board, size, empty_x, empty_y, x1, y1);
	distance2 = find_distance(board, size, empty_x, empty_y, x2, y2);
	distance3 = find_distance(board, size, empty_x, empty_y, x3, y3);
	// If all number are positive, the smaller one moves.		
	if(distance1 >= 0){ // 1 --- positive
		if(distance2 >= 0){ // 2 --- positive
			if(distance3 >= 0){ // 3 --- positive
				if(distance1 <= distance2 && distance1 <= distance3) movement(board, x1, y1, empty_x, empty_y);
				else if(distance2 <= distance1 && distance2 <= distance3) movement(board, x2, y2, empty_x, empty_y);
				else if(distance3 <= distance1 && distance3 <= distance2)	movement(board, x3, y3, empty_x, empty_y);
			}
			else{ // 3 --- negative
				if(distance1 < distance2) movement(board, x1, y1, empty_x, empty_y);
				else	movement(board, x2, y2, empty_x, empty_y);	
			}
		}
		else{ // 2 --- negative
			if(distance3 >= 0){ // 3 --- positive
				if(distance1 < distance3) movement(board, x1, y1, empty_x, empty_y);
				else	movement(board, x3, y3, empty_x, empty_y);
			}
			else	movement(board, x1, y1, empty_x, empty_y); // 3 --- negative
		}
	}
	else{ // distance1 < 0
		if(distance2 >= 0){ // 2 --- positive
			if(distance3 >= 0){ // 3 --- positive
				if(distance2 < distance3) movement(board, x2, y2, empty_x, empty_y);
				else	movement(board, x3, y3, empty_x, empty_y);
			}
			else	movement(board, x2, y2, empty_x, empty_y);  // 3 --- negative
		}
		else{ // 2 --- negative
			if(distance3 >= 0)	movement(board, x3, y3, empty_x, empty_y); // 3 --- positive
			else{ // 3 --- negative 
			// distance1, distance2 and distance3 are negative numbers(if the distance is negative, the number moves away from the corrrect position.), so I found the positive values for them and I chose to move the big one.
				distance1 = abs(distance1);
				distance2 = abs(distance2);
				distance3 = abs(distance3);

				if(distance1 >= distance2 && distance1 >= distance3) movement(board, x1, y1, empty_x, empty_y);
				else if(distance2 >= distance1 && distance2 >= distance3) movement(board, x2, y2, empty_x, empty_y);
				else if(distance3 >= distance1 && distance3 >= distance2)	movement(board, x3, y3, empty_x, empty_y);
			}
		}
	}
}
