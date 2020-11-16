#include<iostream>
#include <string>
#include<fstream>
#include<cstdlib>
#include<time.h>
using namespace std;
#include "boardarray2d.h"

namespace Boards{
	BoardArray2D::BoardArray2D() : AbstractBoard(){
		finalBoard = new string[0];
	}

	BoardArray2D::BoardArray2D(const BoardArray2D& other) : AbstractBoard(other){

		finalBoard = new string[row*column-wall_number];
		for(int i=0; i<row*column-wall_number; i++)
			finalBoard[i] = other.finalBoard[i];

		board = new string*[row];
		for(int i=0; i<row; i++)
			board[i] = new string[column];

		for(int i=0; i<row; i++){
			for(int j=0; j<column; j++)
				board[i][j] = other.board[i][j];
		}
	}

	void BoardArray2D::operator=(const BoardArray2D& other){
		empty_x = other.empty_x;
		empty_y = other.empty_y;

		if(row != other.row && column != other.column){
			delete [] finalBoard;
			finalBoard = new string[other.row*other.column-other.wall_number];

			for(int i=0; i<row; i++)
				delete [] board[i];
			delete [] board;
			board = new string*[other.row];
			for(int i=0; i<other.row; i++)
				board[i] = new string[other.column];
		}
		row = other.row;
		column = other.column;
		wall_number = other.wall_number;

		for(int i=0; i<row*column-wall_number; i++)
			finalBoard[i] = other.finalBoard[i];	

		for(int i=0; i<row; i++){
			for(int j=0; j<column; j++)
				board[i][j] = other.board[i][j];
		}
	}

	string BoardArray2D::operator()(const int x, const int y) const{
		return board[x][y];
	}

	bool BoardArray2D::operator==(AbstractBoard& other){
		if(this->row == other.getRow() && this->column == other.getColumn()){
			for(int i=0; i<row; i++){
				for(int j=0; j<column; j++){
					if(this->operator()(i,j) != other(i,j))	return false;
				}
			}
		}
		else	return false;
		return true;
	}

	void BoardArray2D::setSize(int size1, int size2){
		row = size1;
		column = size2;
		board = new string*[row];
		for(int i=0; i<row; i++)
			board[i] = new string[column];
		setFinalBoard();
	}

	void BoardArray2D::print() const{
		int i, j;
		cout << endl;
		for(i=0; i<row; i++){
			for(j=0; j<column; j++){
				cout.width(5);
				if(board[i][j] == "bb")	cout << " ";
				else if(board[i][j] == "00")	cout << "*";
				else	cout << board[i][j];
			}
			cout << endl;
		}
		cout << endl;
	}

	void BoardArray2D::calculateWallNumber(){ // this function calculates the number of wall in the game.
		int i, j;
		wall_number = 0;

		for(i=0; i<row; i++){
			for(j=0; j<column; j++){
				if(board[i][j] == "00") wall_number++;
			}
		}
	}

	void BoardArray2D::setFinalBoard(){ //this function fills the array accordig to the final board.
		calculateWallNumber();
		finalBoard = new string[row*column-wall_number];

		if(row*column-wall_number > 0){
			int i, j, num1 = 50, num2 = 49;
			string number = "01";

			for(i=0; i<row*column-1-wall_number; i++){
			// I filled the array with the numbers in the game with using ascii table. I used the array to compare the correct board with the current board and fill the final board. 
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

	void BoardArray2D::initRandomBoard(){
		srand(time(NULL));
		int temp[9][9], control_array[row*column], i, j, counter;
		bool flag;
		auto size = 0; // this variable is the size of control_array

		for(i=0; i<row; i++){
			for(j=0; j<column; j++){
				do{
					counter = 0;
					temp[i][j] = rand() % (row*column);
					for(int n=0; n<size; n++)
						if(temp[i][j] == control_array[n]) counter++; // if the random number exists in the array, this counter increases. so flag is false.
					if(counter == 0)	flag = true;
					else	flag = false;
				}while(flag != true);
				control_array[size] = temp[i][j];
				size++;
			}
		}

		//fill the board
		string number[row*column];
		int k = 0;
		//I convert integer array to string array.
		for(i=0; i<row; i++){
			for(j=0; j<column; j++){
				if(temp[i][j] > 9){
					number[k] += (temp[i][j] / 10 + 48);
					number[k] += (temp[i][j] % 10 + 48);
				}
				else{
					number[k] += '0';
					number[k] += (temp[i][j] + 48);
				}
				if(number[k] == "00")	board[i][j] = "bb";
				else	board[i][j] = number[k];
				k++;
			}
		}
		findEmptyCell();
	}

	bool BoardArray2D::isSolved(){
		//this function checks if this board is solved.
		int i, j, num1 = 50, num2 = 49;
		string number = "01";

		int k = 0;
		for(i=0; i<row; i++){
			for(j=0; j<column; j++){
				if(board[i][j] != "00"){
					if( board[i][j] !=  finalBoard[k] )	return false;
					k++;
				}
			}
		}
		return true;
	}

	void BoardArray2D::reset(){
		int i, j;

		auto k = 0;
		for(i=0; i<row; i++){ // I filled the board with the numbers in the array(numbers).
			for(j=0; j<column; j++){
				if(board[i][j] != "00"){
					board[i][j] = finalBoard[k];
					k++;
				}
			}
		}
		number_of_moves = 0;
	}

	void BoardArray2D::readFromFile(string file_name){ // this function reads the file.
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
		int x = 0, y = 0;
		gameBoard.open(file_name);
		while(gameBoard >> board[x][y]){
			y++;
			if(y % size2 == 0){ // when reaches the end of the line, the number of rows increases.
				y = 0;
				x++;
			}
		}
		gameBoard.close();

		findEmptyCell();
		setFinalBoard(); /* I call this function again(previously called in setSize(line238))
		because the wall_number was not known because the file was not read.*/
		setNumberOfMoves(0);
	}

	void BoardArray2D::writeToFile() const{
		string file_name;
		int i, j;

		cout << "Please enter the file name(.txt) you want to save: " << endl;
		cin >> file_name;
		
		ofstream saveBoard;
		saveBoard.open(file_name);
		for(i=0; i<row; i++){
			for(j=0; j<column; j++){
				if(j == column-1)	saveBoard << board[i][j];
				else	saveBoard << board[i][j] << " ";
			}
			saveBoard << endl;
		}
		saveBoard.close();
	}

	void BoardArray2D::move(char choice){
		bool flag;
		findEmptyCell();
		switch(choice){
			case 'L':	case 'l':	//LEFT
				if(empty_y > 0)
					flag = movement(empty_x, empty_y-1);
			break;

			case 'R':	case 'r':	//RIGHT
				if(empty_y < column-1)
					flag = movement(empty_x, empty_y+1);
			break;

			case 'U':	case 'u':	//UP
				if(empty_x > 0)
					flag = movement(empty_x-1, empty_y);
			break;

			case 'D':	case 'd':	//DOWN
				if(empty_x < row-1)
					flag = movement(empty_x+1, empty_y);
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
	}

	bool BoardArray2D::movement(int x, int y){ // this function swaps the two coordinates.
		string temp;

		findEmptyCell(); // this function find the empty cell's current coordinates.
		if(board[x][y] != "00"){ // if the block is wall, the empty cell do not move.
			temp = board[empty_x][empty_y];
			board[empty_x][empty_y] = board[x][y];
			board[x][y] = temp;
			return true;
		}
		return false;
	}

	void BoardArray2D::findEmptyCell(){ // this function find the empty cell's current coordinates.
		int i, j;
		for(i=0; i<row; i++){
			for(j=0; j<column; j++){
				if(board[i][j] == "bb"){
					empty_x = i;
					empty_y = j;
				}
			}
		}
	}

	BoardArray2D::~BoardArray2D(){
		delete [] finalBoard;

		for(int i=0; i<row; i++)
			delete [] board[i];
		delete [] board;
	}
}