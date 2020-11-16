#include<iostream>
#include "nPuzzle.h"
#include<ctime>
#include<cstdlib>

using namespace std;

int main(){
	
	srand( time(NULL) );
	 
	int board[9][9], size /*the size of board*/, counter = 1 /*number of moves*/, x = 0, y = 0 /*x and y empty cell's coordinates*/;
	char choice, quit = 's';
	bool  control /*it controls the end of the game*/;

	menu();

	do{
		cout << "Please enter the problem size(3 <= size <= 9)" << endl;
		cin >> size;
	}while(size < 3 || size > 9);

	//fill the board
	random_board(board, size); // this function determines the elements of the board

	//print the board
	cout << "Your initial random board is" << endl;
	print_board(board, size);
	cout << endl;

	while(control != true && choice != 'Q'){
		cout << "Your move: ";
		cin >> choice;

		find_empty_cell(board, size, x, y); // this function finds the empty cell's coordinates

		switch(choice){
			case 'L': //LEFT
				if(y > 0)	movement(board, x, y, x, y-1);	
				else	cout << "The empty cell cannot move. Please try again." << endl << endl;
			break;

			case 'R': //RIGHT
				if(y < size-1)	movement(board, x, y, x, y+1);	
				else	cout << "The empty cell cannot move. Please try again." << endl << endl;
			break;

			case 'U': //UP
				if(x > 0)	movement(board, x, y, x-1, y);	
				else	cout << "The empty cell cannot move. Please try again." << endl;
			break;

			case 'D': //DOWN
				if(x < size-1)	movement(board, x, y, x+1, y);	
				else	cout << "The empty cell cannot move. Please try again." << endl;
			break;

			case 'I': //INTELLIGENT
				intelligent_move(board, size, x, y);
			break;

			case 'S': //SHUFFLE
				shuffle_move(board, size);
			break;

			case 'Q': //QUIT
				cout << "You are exiting.." << endl;
				quit = 'q';
			break;
			default: cout << "This is invalid choice!" << endl;
		} //end of switch

		if( quit != 'q' ){
			cout << "Your new board is: " << endl;
			print_board(board, size);
		}
		cout << endl;
		cout << "Total number of moves " << counter << endl << endl;
		counter++;

		control = control_positions(board, size); // this function checks the numbers location.
		if(control == true)	cout << "Problem Solved!" << endl;
	} //end of while

	return 0;
}
