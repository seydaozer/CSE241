#include<iostream>
#include <string>
#include<fstream>
#include<cstdlib>
#include<time.h>
using namespace std;
#include "boardarray1d.h"

namespace Boards{
	BoardArray1D::BoardArray1D() : AbstractBoard(){
		finalBoard = new string[0];
		board = new string[0];
	}

	BoardArray1D::BoardArray1D(const BoardArray1D& other) : AbstractBoard(other){
	
		finalBoard = new string[row*column-wall_number];
		for(int i=0; i<row*column-wall_number; i++)
			finalBoard[i] = other.finalBoard[i];

		board = new string[row*column];

		for(int i=0; i<row*column; i++)
			board[i] = other.board[i];
	}

	void BoardArray1D::operator=(const BoardArray1D& other){
		empty_x = other.empty_x;
		empty_y = other.empty_y;
		empty = empty;

		if(row != other.row && column != other.column){
			delete [] finalBoard;
			finalBoard = new string[other.row*other.column-other.wall_number];

			delete [] board;
			board = new string[other.row*other.column];
		}
		
		row = other.row;
		column = other.column;
		wall_number = other.wall_number;

		for(int i=0; i<row*column-wall_number; i++)
			finalBoard[i] = other.finalBoard[i];	

		for(int i=0; i<row*column; i++)
			board[i] = other.board[i];
		
	}

	bool BoardArray1D::operator==(AbstractBoard& other){
		if(this->row == other.getRow() && this->column == other.getColumn()){
			for(int i=0; i<row; i++){
				for(int j=0; j<column; j++){
					if( this->operator()(i, j) != other(i, j) ) return false;
				}
			}
		}
		else	return false;
		return true;
	}

	void BoardArray1D::move(char choice){
		bool flag;
		findEmptyCell();
		switch(choice){
			case 'L':	case 'l':	//LEFT
				if(empty_y > 0)
					flag = movement(empty-1);
				else	cout << "LEFT is invalid move!\n";
			break;

			case 'R':	case 'r':	//RIGHT
				if(empty_y < column-1)
					flag = movement(empty+1);
				else	cout << "RIGHT is invalid move!\n";
			break;

			case 'U':	case 'u':	//UP
				if(empty_x > 0)
					flag = movement(empty-column);
				else	cout << "UP is invalid move!\n";
			break;

			case 'D':	case 'd':	//DOWN
				if(empty_x < row-1)
					flag = movement(empty+column);
				else	cout << "DOWN is invalid move!\n";
			break;
		}
		if(flag == true){
			if(choice == 'L' || choice == 'l')	cout << "your move is Left" << endl;
			else if(choice == 'R' || choice == 'r')	cout << "your move is Right" << endl;
			else if(choice == 'U' || choice == 'u')	cout << "your move is Up" << endl;
			else if(choice == 'D' || choice == 'd')	cout << "your move is Down" << endl;
			number_of_moves ++;
			setLastMove(choice);
		}
		else	cout << "this is invalid move!\n";
	}

	bool BoardArray1D::movement(int i){ // this function swaps the two coordinates.
		string temp;

		findEmptyCell(); // this function find the empty cell's current coordinates.
		if(board[i] != "00"){ // if the block is wall, the empty cell do not move.
			temp = board[empty];
			board[empty] = board[i];
			board[i] = temp;
			return true;
		}
		return false;
	}

	void BoardArray1D::setSize(int size1, int size2){
		row = size1;
		column = size2;
		board = new string[row*column];
		setFinalBoard();
	}

	string BoardArray1D::operator()(const int x, const int y) const{
		int index = x*column + y;
		return board[index];
	}

	bool BoardArray1D::isSolved(){
		//this function checks if this board is solved.
		int num1 = 50, num2 = 49;
		string number = "01";

		int k = 0;
		for(int i=0; i<row*column; i++){
			if(board[i] != "00"){
				if( board[i] !=  finalBoard[k] )	return false;
				k++;
			}
		}
		return true;
	}

	void BoardArray1D::setFinalBoard(){ //this function fills the array accordig to the final board.
		calculateWallNumber();
		finalBoard = new string[row*column-wall_number];

		if(row*column-wall_number > 0){
			int i, j, num1 = 50, num2 = 49;
			string number = "01";

			for(i=0; i<row*column-1-wall_number; i++){ // I filled the array with the numbers in the game with using ascii table. I used the array to compare the correct board with the current board and fill the final board. 
				finalBoard[i] = number;
				if(num1 > 57){
					num1 = 48;
					number[0] = num2;
					num2++;
				}
				number[1] = num1;
				num1++;
			}

			finalBoard[row*column-1-wall_number] = "bb"; // I put 0 on the last element of the array for the empty cell.
		}
	}

	void BoardArray1D::calculateWallNumber(){ // this function calculates the number of wall in the game.
		wall_number = 0;

		for(int i=0; i<row*column; i++)
				if(board[i] == "00") wall_number++;

	}

	void BoardArray1D::print() const{
		int i;
		cout << endl;
		for(i=0; i<row*column; i++){
			cout.width(5);
			if(board[i] == "bb")	cout << " ";
			else if(board[i] == "00")	cout << "*";
			else	cout << board[i];
			if(i % column == column-1)	cout << endl;
		}
		cout << endl;
	}

	void BoardArray1D::readFromFile(string file_name){ // this function reads the file.
		setSize(0, 0);
		string line;
		bool flag;
		int size1 = 0, size2 = 0;

		fstream gameBoard;
		do{
			gameBoard.open(file_name);
			if( gameBoard.is_open() ){
			flag = true;
			}
			else{
				cout << "Please enter the file name(.txt) you want to play." << endl;
				cin >> file_name;
				flag = false;
			}
		}while(flag != true);

		while( getline(gameBoard, line) )
			size1++; // the number of row
		
		int i = 0;
		while(i < 25){
				if(line[i] == ' ')	size2++; // the number of column
				i++;
		}
		size2 += 1;
		gameBoard.close();

		setSize(size1, size2);
		i = 0;
		gameBoard.open(file_name);
		while(gameBoard >> board[i]){
			i++;
		}
		gameBoard.close();

		findEmptyCell();
		setFinalBoard(); /* I call this function again(previously called in setSize(line267))
		because the wall_number was not known because the file was not read.*/
		setNumberOfMoves(0);
	}

	void BoardArray1D::writeToFile() const{
		string file_name;

		cout << "Please enter the file name(.txt) you want to save: " << endl;
		cin >> file_name;
		
		ofstream saveBoard;
		saveBoard.open(file_name);
		for(int i=0; i<row*column; i++){
			if(i % column == column-1)	saveBoard << board[i];
			else	saveBoard << board[i] << " ";
			if(i % column == column-1)	saveBoard << endl;
		}
		saveBoard.close();
	}

	void BoardArray1D::reset(){

		auto k = 0;
		for(int i=0; i<row*column; i++){ // I filled the board with the numbers in the array(numbers).
			if(board[i] != "00"){
				board[i] = finalBoard[k];
				k++;
			}
		}
		setNumberOfMoves(0);
	}

	void BoardArray1D::initRandomBoard(){
		srand(time(NULL));
		int temp[9*9], control_array[row*column], i, j, counter;
		bool flag;
		auto size = 0; // this variable is the size of control_array

		for(i=0; i<row*column; i++){
			do{
				counter = 0;
				temp[i] = rand() % (row*column);
				for(int n=0; n<size; n++)
					if(temp[i] == control_array[n]) counter++; // if the random number exists in the array, this counter increases. so flag is false.
				if(counter == 0)	flag = true;
				else	flag = false;
			}while(flag != true);
			control_array[size] = temp[i];
			size++;
		}

		//fill the board
		string number[row*column];
		int k = 0;
		//I convert integer array to string array.
		for(i=0; i<row*column; i++){
			if(temp[i] > 9){
				number[k] += (temp[i] / 10 + 48);
				number[k] += (temp[i] % 10 + 48);
			}
			else{
				number[k] += '0';
				number[k] += (temp[i] + 48);
			}
			if(number[k] == "00")	board[i] = "bb";
			else	board[i] = number[k];
			k++;
		}

		findEmptyCell();
	}

	void BoardArray1D::findEmptyCell(){ // this function find the empty cell's current coordinates.

		for(int i=0; i<row*column; i++){
			if(board[i] == "bb"){
				empty_x = i/column;
				empty_y = i%column;
				empty = i;
			}
		}
	}

	BoardArray1D::~BoardArray1D(){
		delete [] finalBoard;
		delete [] board;
	}
}