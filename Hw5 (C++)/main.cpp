#include "boardarray2d.h"
#include "boardvector.h"
#include "boardarray1d.h"
#include "abstractboard.h"
#include <iostream>
#include<vector>
using namespace std;
using namespace Boards;

int main(){
	string file_name = "game.txt";
	int choice;
	cout << "Please, enter the board type" << endl;
	cout << "1- BoardVector(The Board is represented using an STL vector of STL vectors.)" << endl;
	cout << "2- BoardArray2D(The Board is represented using a one dimensional dynamic C array.)" << endl;
	cout << "3- BoardArray1D(The Board is represented using a two dimensional dynamic C array.)" << endl;
	cin >> choice;

	if(choice == 1){ //BoardVector
		BoardVector b1, b2;
		b1.readFromFile(file_name);
		cout << "The first board:\n";
		b1.print();
		b2.setSize(4, 4);
		b2.initRandomBoard();
		cout << "The second board:\n";
		b2.print();

		if(b1 == b2)	cout << "These two boards are equal." << endl;
		else	cout << "These two boards are not equal." << endl;
		b2 = b1;
		if(b1 == b2)	cout << "These two boards are equal." << endl;
		else	cout << "These two boards are not equal." << endl;

		vector <AbstractBoard *> boards;
		boards.push_back(&b1);
		boards.push_back(&b2);

		if(validMoves(boards) == true)	cout << "This array contains a valid sequence of moves for a solution." << endl;
		else	cout << "This array does not contain a valid sequence of moves for a solution." << endl;

		BoardVector b3(b1);
		b3.print();
		if(b3.isSolved() == true)	cout << "This board is solved." << endl;
		else	cout << "This board is not solved." << endl;
		b3.reset();
		b3.print();
		if(b3.isSolved() == true)	cout << "This board is solved." << endl;
		else	cout << "This board is not solved." << endl;

		b3.move('L');
		b3.move('U');
		b3.move('R');
		b3.move('D');
		cout << "The last move is: " << b3.lastMove() << endl;

		cout << "The board number which has been created so far: " << b3.NumberOfBoards() << endl;;

		b2.writeToFile();
	}
		
	else if(choice == 2){ //BoardArray2D
		BoardArray2D b1, b2;
		b1.readFromFile(file_name);
		cout << "The first board:\n";
		b1.print();
		b2.setSize(4, 4);
		b2.initRandomBoard();
		cout << "The second board:\n";
		b2.print();

		if(b1 == b2)	cout << "These two boards are equal." << endl;
		else	cout << "These two boards are not equal." << endl;
		b2 = b1;
		if(b1 == b2)	cout << "These two boards are equal." << endl;
		else	cout << "These two boards are not equal." << endl;

		vector <AbstractBoard *> boards;
		boards.push_back(&b1);
		boards.push_back(&b2);

		if(validMoves(boards) == true)	cout << "This array contains a valid sequence of moves for a solution." << endl;
		else	cout << "This array does not contain a valid sequence of moves for a solution." << endl;

		BoardArray2D b3(b1);
		b3.print();
		if(b3.isSolved() == true)	cout << "This board is solved." << endl;
		else	cout << "This board is not solved." << endl;
		b3.reset();
		b3.print();
		if(b3.isSolved() == true)	cout << "This board is solved." << endl;
		else	cout << "This board is not solved." << endl;

		b3.move('L');
		b3.move('U');
		b3.move('R');
		b3.move('D');
		cout << "The last move is: " << b3.lastMove() << endl;

		cout << "The board number which has been created so far: " << b3.NumberOfBoards() << endl;;

		b2.writeToFile();
	}

	else if(choice == 3){ //BoardArray1D
		BoardArray1D b1, b2;
		b1.readFromFile(file_name);
		cout << "The first board:\n";
		b1.print();
		b2.setSize(4, 4);
		b2.initRandomBoard();
		cout << "The second board:\n";
		b2.print();

		if(b1 == b2)	cout << "These two boards are equal." << endl;
		else	cout << "These two boards are not equal." << endl;
		b2 = b1;
		if(b1 == b2)	cout << "These two boards are equal." << endl;
		else	cout << "These two boards are not equal." << endl;

		vector <AbstractBoard *> boards;
		boards.push_back(&b1);
		boards.push_back(&b2);

		if(validMoves(boards) == true)	cout << "This array contains a valid sequence of moves for a solution." << endl;
		else	cout << "This array does not contain a valid sequence of moves for a solution." << endl;

		BoardArray1D b3(b1);
		b3.print();
		if(b3.isSolved() == true)	cout << "This board is solved." << endl;
		else	cout << "This board is not solved." << endl;
		b3.reset();
		b3.print();
		if(b3.isSolved() == true)	cout << "This board is solved." << endl;
		else	cout << "This board is not solved." << endl;

		b3.move('L');
		b3.move('U');
		b3.move('R');
		b3.move('D');
		cout << "The last move is: " << b3.lastMove() << endl;

		cout << "The board number which has been created so far: " << b3.NumberOfBoards() << endl;;

		b2.writeToFile();
	}

	return 0;
}