#include<iostream>
#include "nPuzzle.h"

using namespace std;

void menu(){

	cout << "------------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "(L)-> moves the empty cell left if there is room" << endl;
	cout << "(R)-> moves the empty cell right if there is room" << endl;
	cout << "(U)-> moves the empty cell up if there is room" << endl;
	cout << "(D)-> moves the empty cell down if there is room" << endl;
	cout << "(I)-> Intelligent move moves the blank tile in a way that after the move, the tiles are closer to their final positions." << endl;
	cout << "(S)-> Shuffle- takes the board to the final solution, and makes size*size random moves to shuffle the board." << endl;
	cout << "(Q)-> Quits the game" << endl;
	cout << "------------------------------------------------------------------------------------------------------------------------" << endl << endl;

}
