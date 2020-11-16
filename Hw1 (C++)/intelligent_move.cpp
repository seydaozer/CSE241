#include<iostream>
#include "nPuzzle.h"

using namespace std;

void intelligent_move(int board[][9],int size, int empty_x,int empty_y){
	int temp_x, temp_y;
	int previous_empty_x = empty_x, previous_empty_y = empty_y;

	if(empty_y == 0){ // first column 
		if(empty_x == 0){ // (0,0)
			two_locate_move(board, size, empty_x, empty_y, 0, 1, 1, 0);			
		}
		else if(empty_x == size-1){ // ( size-1, 0)
			two_locate_move(board, size, empty_x, empty_y, size-2, 0, size-1, 1);
		}
		else{ // (  , 0) for edges
			for(temp_x=1; temp_x<size-1; temp_x++){
				if(empty_x == temp_x)
					three_locate_move(board, size, empty_x, empty_y, temp_x+1, 0, temp_x-1, 0, temp_x, 1);
			}
		}
	}
	else if(empty_y == size-1){ // last column
		if(empty_x == 0){ // ( 0, size-1)
			two_locate_move(board, size, empty_x, empty_y, 0, size-2, 1, size-1);
		}
		else if(empty_x == size-1){ // ( size-1, size-1)
			two_locate_move(board, size, empty_x, empty_y, size-1, size-2, size-2, size-1);
		}
		else{ // (  , size-1) for edges
			for(temp_x=1; temp_x<size-1; temp_x++){
				if(empty_x == temp_x)
					three_locate_move(board, size, empty_x, empty_y, temp_x+1, size-1, temp_x-1, size-1, temp_x, size-2);
			}
		}
	}
	else if(empty_x == 0){ // first row
		// (0, 0)
		// ( 0, size-1)
		if(empty_y != 0 && empty_y != size-1){ // ( 0,  ) for edges
			for(temp_y=1; temp_y<size-1; temp_y++){
				if(empty_y == temp_y)
					three_locate_move(board, size, empty_x, empty_y, 0, temp_y-1, 0, temp_y+1, 1, temp_y);
			}
		}
	}
	else if(empty_x == size-1){ //last row
		// ( size-1, 0)
		// ( size-1, size-1)
		if(empty_y != 0 && empty_y != size-1) { // ( size-1,  ) for edges
			for(temp_y=1; temp_y<size-1; temp_y++){
				if(empty_y == temp_y)
					three_locate_move(board, size, empty_x, empty_y, size-1, temp_y-1, size-1, temp_y+1, size-2, temp_y);
			}
		}
	}
	else{ // for middle sections
		for(temp_x=1; temp_x<=size-2; temp_x++){	
			for(temp_y=1; temp_y<=size-2; temp_y++){
				if(empty_y == temp_y && empty_x == temp_x)
					four_locate_move(board, size, empty_x, empty_y, temp_x, temp_y-1, temp_x, temp_y+1, temp_x-1, temp_y, temp_x+1, temp_y);
			}
		}
	}

	find_empty_cell(board, size, empty_x, empty_y); // I found the empty cell's current coordinates
	// I determine the direction of movement based on the empty cell's coordinates.
	if(previous_empty_x - empty_x > 0 && previous_empty_x - empty_x != 0)
		cout << "Intelligent move chooses U" << endl << endl;
	else if(previous_empty_x - empty_x != 0)	cout << "Intelligent move chooses D" << endl << endl;

	if(previous_empty_y - empty_y > 0 && previous_empty_y - empty_y != 0)
		cout << "Intelligent move chooses L" << endl << endl;
	else if(previous_empty_y - empty_y != 0)	cout << "Intelligent move chooses R" << endl << endl;

}
