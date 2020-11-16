#include<iostream>
#include<string>
#include<fstream>
#include<ctime>
#include<cstdlib>

using namespace std;

class NPuzzle{

private:
	class Board{
	private:
		string board[9][9];
		int row;
		int column;
		int empty_x;
		int empty_y;
		int wall_number; // the number of wall in the game.
	public:	
		void print();
		void readFromFile(string file_name);
		void writeToFile();
		void reset();
		void setSize();
		void move(char choice, bool& flag);
		bool isSolved();
		void initRandomBoard();
		void fillFinalBoard(string numbers[]);
		void calculateWallNumber();
		bool movement(const int x, const int y);
		void findEmptyCell();
		void accessSize(int& size1, int& size2) const;
		void twoBlockMove(const int x1, const int y1, const int x2, const int y2);
		inline int findDistance(int block_x, int block_y);
		void findCurrentNumber(string block, string& number);
		void findTrueCoordinates(string block, int& x, int& y);
		void threeBlockMove(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3);
		void fourBlockMove(const int x1, const int y1, const int x2, const int y2, const int x3, const int y3, const int x4, const int y4);
		void accessEmptyCell(int& x, int& y);
	};
	int previous_move; // I used this variable to avoid repetetion of motion in moveRandom function.
public:
	void print();
	void printReport(int counter);
	void readFromFile(string file_name);
	void writeToFile();
	bool shuffle(int N);
	void reset();
	void setSize();
	void moveRandom(int numberOfMoves);
	bool moveIntelligent();
	bool move(char choice, bool& flag);
	bool solvePuzzle(int& counter);
	void Menu();
	Board gameBoard;
};

int main(int argc, char *argv[]){
	NPuzzle Puzzle;

	if(argc == 1){ // random board
		Puzzle.setSize();
	}
	else if(argc == 2){ // board in the file
		Puzzle.readFromFile(*(argv+1));
	}

	cout << "Your initial random board is" << endl;
	Puzzle.print();
	Puzzle.Menu();

	return 0;
}

void NPuzzle::Menu(){
	auto counter = 1 /*number of moves*/;
	char choice , quit = 's';
	auto control = false; // I use this variable to check if the game is over.
	bool flag; // I use this variable to check if the empty cell is moving.
	string file_name;
	int size1;
	decltype(size1) size2; // these variables are the board size.

	cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "(V) Solves the puzzle." << endl;
	cout << "(T) Prints a report about how many moves have been done and if the solution is found." << endl;
	cout << "(E) Enter a file name for saves the current board configuration as a loadable shape file." << endl;
	cout << "(O) Enter a file name and loads the current board configuration from the shape file." << endl;
	cout << "(L) moves the empty cell left if there is room" << endl;
	cout << "(R) moves the empty cell right if there is room" << endl;
	cout << "(U) moves the empty cell up if there is room" << endl;
	cout << "(D) moves the empty cell down if there is room" << endl;
	cout << "(I) Intelligent move moves the blank tile in a way that after the move, the tiles are closer to their final positions." << endl;
	cout << "(S) Shuffle- takes the board to the final solution, and makes size*size random moves to shuffle the board." << endl;
	cout << "(Q) Quits the game" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------" << endl << endl;

	while(control != true && quit != 'q'){
		cout << "Your move: ";
		cin >> choice;
		switch(choice){
			case 'V':	case 'v':	//SOLVE
				control = solvePuzzle(counter);
			break;

			case 'T':	case 't':	//PRINT REPORT
				counter--;
				printReport(counter);	
			break;

			case 'E':	case 'e':	//WRITE FILE
				writeToFile();
				counter--;
			break;

			case 'O':	case 'o':	//READ FILE
				cout << "Please enter the file name(.txt) you want to load." << endl;
				cin >> file_name;
				readFromFile(file_name);
				counter = 0;
			break;

			case 'L':	case 'l':	//LEFT
			case 'R':	case 'r':	//RIGHT
			case 'U':	case 'u':	//UP
			case 'D':	case 'd':	//DOWN
				control = move(choice, flag);
				if(flag == false)	counter--;
			break;

			case 'I':	case 'i':	//INTELLIGENT
				control = moveIntelligent();
			break;

			case 'S':	case 's':	//SHUFFLE
				gameBoard.accessSize(size1, size2);
				control = shuffle(size1*size2);
				counter += size1*size2;
				counter--;
			break;

			case 'Q':	case 'q':	//QUIT
				cout << "You are exiting.." << endl;
				quit = 'q';
			break;
	
			default: cout << "This is invalid choice!" << endl;
		} //end of switch
		if(quit != 'q'){
				cout << "Your new board is: " << endl;
				print();
			}
		printReport(counter);
		counter++;	
	}
}

bool NPuzzle::solvePuzzle(int& counter){
	int number_of_random = 3, number_of_intelligent = 4, i;
	bool control;
	while(gameBoard.isSolved() != true){
		if(counter >= 100000){
			number_of_random = 2;
		}
		//random move
		moveRandom(number_of_random);
		counter += number_of_random;
		printReport(counter);
		//intelligent move
		i = 0;
		do{
			control = moveIntelligent();
			gameBoard.print();
			i++;
			counter++;//this variable is the number of moves in the game.
		}while(i < number_of_intelligent && control != true);
		printReport(counter);
	}
	return gameBoard.isSolved();
}

bool NPuzzle::moveIntelligent(){
	// In this function I determine the numbers around the empty cell and calculate the distance between these number and these numbers's correct position in the game.
	int row, column;
	gameBoard.accessSize(row, column);

	int temp_x, temp_y, empty_x , empty_y;
	gameBoard.accessEmptyCell(empty_x, empty_y);
	int previous_empty_x = empty_x, previous_empty_y = empty_y; // I use these variables for empty cell's previous coordinates. I determine the direction of movement according to the difference between these coordinates.
	
	if(empty_y == 0){ // first column 
		if(empty_x == 0) // (0,0)
			gameBoard.twoBlockMove(0, 1, 1, 0);
		else if(empty_x == row-1) // ( row-1, 0)
			gameBoard.twoBlockMove(row-2, 0, row-1, 1);
		else{ // (  , 0) for edges 
			for(temp_x=1; temp_x<row-1; temp_x++){
				if(empty_x == temp_x)
					gameBoard.threeBlockMove(temp_x+1, 0, temp_x-1, 0, temp_x, 1);
			}
		}
	}
	else if(empty_y == column-1){ // last column
		if(empty_x == 0) // ( 0, column-1)
			gameBoard.twoBlockMove(0, column-2, 1, column-1);
		else if(empty_x == row-1) // ( row-1, column-1)
			gameBoard.twoBlockMove(row-1, column-2, row-2, column-1);
		else{ // (  , column-1) for edges
			for(temp_x=1; temp_x<row-1; temp_x++){
				if(empty_x == temp_x)
					gameBoard.threeBlockMove(temp_x+1, column-1, temp_x-1, column-1, temp_x, column-2);
			}
		}
	}
	else if(empty_x == 0){ // first row
		// (0, 0)
		// ( 0, column-1)
		if(empty_y != 0 && empty_y != column-1){ // ( 0,  ) for edges
			for(temp_y=1; temp_y<column-1; temp_y++){
				if(empty_y == temp_y)
					gameBoard.threeBlockMove(0, temp_y-1, 0, temp_y+1, 1, temp_y);
			}
		}
	}
	else if(empty_x == row-1){ //last row
		// ( row-1, 0)
		// ( row-1, column-1)
		if(empty_y != 0 && empty_y != column-1) { // ( row-1,  ) for edges
			for(temp_y=1; temp_y<column-1; temp_y++){
				if(empty_y == temp_y)
					gameBoard.threeBlockMove(row-1, temp_y-1, row-1, temp_y+1, row-2, temp_y);
			}
		}
	}
	else{ // for middle sections
		for(temp_x=1; temp_x<=row-2; temp_x++){	
			for(temp_y=1; temp_y<=column-2; temp_y++){
				if(empty_y == temp_y && empty_x == temp_x)
					gameBoard.fourBlockMove(temp_x, temp_y-1, temp_x, temp_y+1, temp_x-1, temp_y, temp_x+1, temp_y);
			}
		}
	}
	gameBoard.accessEmptyCell(empty_x, empty_y); // I found the empty cell's current coordinates
	// I determine the direction of movement based on the empty cell's coordinates.
	if(previous_empty_x - empty_x > 0 && previous_empty_x - empty_x != 0)
		cout <<  "Intelligent move chooses U" << endl;

	else if(previous_empty_x - empty_x != 0)
		cout << "Intelligent move chooses D" << endl;

	if(previous_empty_y - empty_y > 0 && previous_empty_y - empty_y != 0)
		cout << "Intelligent move chooses L" << endl;
	else if(previous_empty_y - empty_y != 0)	cout << "Intelligent move chooses R"  << endl;

	return gameBoard.isSolved();
}

void NPuzzle::Board::accessEmptyCell(int& x, int& y){
	findEmptyCell();
	x = empty_x;
	y = empty_y;
}

void NPuzzle::Board::twoBlockMove(int x1, int y1, int x2, int y2){
	bool flag = false; // if the empty cell do not move, the flag is false.
	findEmptyCell();
	auto distance1 = findDistance(x1, y1);
	auto distance2 = findDistance(x2, y2);
	// If all number are positive, the smaller one moves.	
	if(distance1 > 0 && distance2 < 0 && board[x1][y1] != "00"){
		movement(x1, y1);
		flag = true;
	}
	else if(distance1 < 0 && distance2 > 0 && board[x2][y2] != "00"){
		movement(x2, y2);
		flag = true;
	}
	else if(board[x1][y1] != "00" && board[x2][y2] != "00"){ // distance1 and distance2 are negative numbers(if the distance is negative, the number moves away from the corrrect position.), so I found the positive values for them and I chose to move the big one.
		distance1 = abs(distance1);
		distance2 = abs(distance2);
		if(distance1 > distance2) movement(x1, y1);
		else	movement(x2, y2);
		flag = true;
	}
	if(flag == false){
		if(board[x1][y1] != "00") movement(x1, y1);
		else if(board[x2][y2] != "00")	movement(x2, y2);
	}
}

void NPuzzle::Board::threeBlockMove(int x1, int y1, int x2, int y2, int x3, int y3){
	bool flag = false;
	auto distance1 = findDistance(x1, y1);
	auto distance2 = findDistance(x2, y2);
	auto distance3 = findDistance(x3, y3);
	// If all number are positive, the smaller one moves.		
	if(distance1 >= 0){ // 1 --- positive
		if(distance2 >= 0){ // 2 --- positive
			if(distance3 >= 0){ // 3 --- positive
				if(distance1 <= distance2 && distance1 <= distance3 && board[x1][y1] != "00"){
					movement(x1, y1);
					flag = true;
				}
				else if(distance2 <= distance1 && distance2 <= distance3 && board[x2][y2] != "00"){
					movement(x2, y2);
					flag = true;
				}
				else if(distance3 <= distance1 && distance3 <= distance2 && board[x3][y3] != "00"){
					movement(x3, y3);
					flag = true;
				}
			}
			else{ // 3 --- negative
				if(distance1 < distance2 && board[x1][y1] != "00"){
					movement(x1, y1);
					flag = true;
				}
				else if(board[x2][y2] != "00"){
					movement(x2, y2);
					flag = true;
				}
			}
		}
		else{ // 2 --- negative
			if(distance3 >= 0){ // 3 --- positive
				if(distance1 < distance3 && board[x1][y1] != "00"){
					movement(x1, y1);
					flag = true;
				}
				else if(board[x3][y3] != "00"){
					movement(x3, y3);
					flag = true;
				}
			}
			else if(board[x1][y1] != "00"){
				movement(x1, y1); // 3 --- negative
				flag = true;
			}
		}
	}
	else{ // distance1 < 0
		if(distance2 >= 0){ // 2 --- positive
			if(distance3 >= 0){ // 3 --- positive
				if(distance2 < distance3 && board[x2][y2] != "00"){
					movement(x2, y2);
					flag = true;
				}
				else if(board[x3][y3] != "00"){
					movement(x3, y3);
					flag = true;
				}
			}
			else if(board[x2][y2] != "00"){
					movement(x2, y2);  // 3 --- negative
					flag = true;
			}
		}
		else{ // 2 --- negative
			if(distance3 >= 0 && board[x3][y3] != "00"){
				movement(x3, y3); // 3 --- positive
				flag = true;
			}
			else if(board[x1][y1] != "00" && board[x2][y2] != "00" && board[x3][y3] != "00"){ // 3 --- negative 
			// distance1, distance2 and distance3 are negative numbers(if the distance is negative, the number moves away from the corrrect position.), so I found the positive values for them and I chose to move the big one.
				distance1 = abs(distance1);
				distance2 = abs(distance2);
				distance3 = abs(distance3);

				if(distance1 >= distance2 && distance1 >= distance3) movement(x1, y1);
				else if(distance2 >= distance1 && distance2 >= distance3) movement(x2, y2);
				else if(distance3 >= distance1 && distance3 >= distance2)	movement(x3, y3);
				flag = true;
			}
		}
	}
	if(flag != true){
		if(board[x1][y1] != "00") movement(x1, y1);
		else if(board[x2][y2] != "00")	movement(x2, y2);
		else if(board[x3][y3] != "00")	movement(x3, y3);
	}
}

void NPuzzle::Board::fourBlockMove(int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){
	bool flag = false;
	auto distance1 = findDistance(x1, y1);
	auto distance2 = findDistance(x2, y2);
	auto distance3 = findDistance(x3, y3);
	auto distance4 = findDistance(x4, y4);
	// If all number are positive, the smaller one moves.		
	if(distance1 >= 0){  // distance1 positive
		if(distance2 >= 0){ // distance2 positive (distance1 positive)
			if(distance3 >= 0){ // distance3 positive (distance1 , distance2 positive)
				if(distance4 >= 0){ // distance4 positive (1, 2, 3, 4 positive)
					if(distance1 <= distance2 && distance1 <= distance3 && distance1 <= distance4 && board[x1][y1] != "00"){
						movement(x1, y1);
						flag = true;
					}
					else if(distance2 <= distance1 && distance2 <= distance3 && distance2 <= distance4 && board[x2][y2] != "00"){
						movement(x2, y2);
						flag = true;
					}
					else if(distance3 <= distance1 && distance3 <= distance2 && distance3 <= distance4 && board[x3][y3] != "00"){
						movement(x3, y3);
						flag = true;
					}
					else if(distance4 <= distance1 && distance4 <= distance2 && distance4 <= distance3 && board[x4][y4] != "00"){
						movement(x4, y4);
						flag = true;
					}
				}
				else{ // distance4 negative (1, 2, 3 positive)
					if(distance1 <= distance2 && distance1 <= distance3  && board[x1][y1] != "00"){
						movement(x1, y1);
						flag = true;
					}
					else if(distance2 <= distance1 && distance2 <= distance3 && board[x2][y2] != "00"){
						movement(x2, y2);
						flag = true;
					}
					else if(distance3 <= distance1 && distance3 <= distance2 && board[x3][y3] != "00"){
						movement(x3, y3);
						flag = true;
					}
				}
			}
			else{ // distance3 negative (distance1 , distance2 positive)
				if(distance4 >= 0){ // distance4 positive (1, 2, 4 positive)
					if(distance1 <= distance2 && distance1 <= distance4 && board[x1][y1] != "00"){
						movement(x1, y1);
						flag = true;
					}
					else if(distance2 <= distance1 && distance2 <= distance4 && board[x2][y2] != "00"){
						movement(x2, y2);
						flag = true;
					}
					else if(distance4 <= distance1 && distance4 <= distance2 && board[x4][y4] != "00"){
						movement(x4, y4);
						flag = true;
					}
				}
				else{ // distance4 negative (1, 2 positive)
					if(distance1 < distance2 && board[x1][y1] != "00"){
						movement(x1, y1);
						flag = true;
					}
					else if(board[x2][y2] != "00"){
						movement(x2, y2);
						flag = true;
					}
				}
			}
		}
		else{ // distance2 negative
			if(distance3 >= 0){ // distance3 positive (distance1 positive, distance2 negative)
				if(distance4 >= 0){ // distance4 positive (1, 3, 4 positive)
					if(distance1 <= distance3 && distance1 <= distance4 && board[x1][y1] != "00"){
						movement(x1, y1);
						flag = true;
					}
					else if(distance3 <= distance1 && distance3 <= distance4 && board[x3][y3] != "00"){
						movement(x3, y3);
						flag = true;
					}
					else if(distance4 <= distance1 && distance4 <= distance3 && board[x4][y4] != "00"){
						movement(x4, y4);
						flag = true;
					}
				}
				else{// distance4 negative (1, 3 positive)
					if(distance1 < distance3 && board[x1][y1] != "00"){
						movement(x1, y1);
						flag = true;
					}
					else if(board[x3][y3] != "00"){
						movement(x3, y3);
						flag = true;
					}
				}
			}
			else{ // distance3 negative (distance1 positive, distance2 negative)
				if(distance4 >= 0){ // distance4 positive (1, 4 positive)
					if(distance1 < distance4 && board[x1][y1] != "00"){
						movement(x1, y1);
						flag = true;
					}
					else if(board[x4][y4] != "00"){
						movement(x4, y4);
						flag = true;
					}
				}
				else if(board[x1][y1] != "00"){ // distance4 negative ( 1 positive)
					movement(x1, y1);
					flag = true;
				}
			}
		}
	}
	else{ // distance1 < 0
		if(distance2 >= 0){ // distance2 negative
			if(distance3 >= 0){ // distance3 positive (distance1 negative, distance2 positive)
				if(distance4 >= 0){ // (2, 3, 4 positive)
					if(distance2 <= distance3 && distance2 <= distance4 && board[x2][y2] != "00"){
						movement(x2, y2);
						flag = true;
					}
					else if(distance3 <= distance2 && distance3 <= distance4 && board[x3][y3] != "00"){
						movement(x3, y3);
						flag = true;
					}
					else if(distance4 <= distance2 && distance4 <= distance3 && board[x4][y4] != "00"){
						movement(x4, y4);
						flag = true;
					}
				}
				else{ // distance4 negative (2, 3 positive)
					if(distance2 < distance3 && board[x2][y2] != "00"){
						movement(x2, y2);
						flag = true;
					}
					else if(board[x3][y3] != "00"){
						movement(x3, y3);
						flag = true;
					}
				}
			}
			else{ // distance3 negative (distance1 negative, distance2 positive)
				if(distance4 >= 0){ // (2, 4 positive)
					if(distance2 < distance4 && board[x2][y2] != "00"){
						movement(x2, y2);
						flag = true;
					}
					else if(board[x4][y4] != "00"){
						movement(x4, y4);
						flag = true;
					}
				}
				else if(board[x2][y2] != "00"){ // distance4 negative (2 positive)
					movement(x2, y2);
					flag = true;
				}
			}
		}
		else{ // distance2 negative
			if(distance3 >= 0){ // distance3 positive (distance1, distance2 negative)
				if(distance4 >= 0){ // (3, 4 positive)
					if(distance3 < distance4 && board[x3][y3] != "00"){
						movement(x3, y3);
						flag = true;
					}
					else if(board[x4][y4] != "00"){
						movement(x4, y4);
						flag = true;
					}
				}
				else if(board[x3][y3] != "00"){ // distance4 negative (3 positive)
					movement(x3, y3);
					flag = true;
				}
			}
			else{ // distance3 negative (distance1, distance2 negative)
				if(distance4 >= 0  && board[x4][y4] != "00"){ // (4 positive)
					movement(x4, y4);
					flag = true;
				}
				else if(board[x1][y1] != "00" && board[x2][y2] != "00" && board[x3][y3] != "00" && board[x4][y4] != "00"){ // distance4 negative (1, 2, 3, 4 negative)
				// distance1, distance2 and distance3 are negative numbers(if the distance is negative, the number moves away from the corrrect position.), so I found the positive values for them and I chose to move the big one.
					distance1 = abs(distance1);
					distance2 = abs(distance2);
					distance3 = abs(distance3);
					distance4 = abs(distance4);
					if(distance1 >= distance2 && distance1 >= distance3 && distance1 >= distance4) movement(x1, y1);
					else if(distance2 >= distance1 && distance2 >= distance3 && distance2 >= distance4) movement(x2, y2);
					else if(distance3 >= distance1 && distance3 >= distance2 && distance3 >= distance4)	movement(x3, y3);
					else if(distance4 >= distance1 && distance4 >= distance2 && distance4 >= distance3)	movement(x4, y4);
					flag = true;
				}
			}
		}
	}
	if(flag != true){
		if(board[x1][y1] != "00") movement(x1, y1);
		else if(board[x2][y2] != "00")	movement(x2, y2);
		else if(board[x3][y3] != "00") movement(x3, y3);
		else if(board[x4][y4] != "00")	movement(x4, y4);
	}
}

inline int NPuzzle::Board::findDistance(int block_x, int block_y){
	int distance1, distance2, x, y;
	string number;
	findEmptyCell();
	findCurrentNumber(board[block_x][block_y], number); // this function finds the number in the current block
	findTrueCoordinates(number, x, y); // this function finds the correct coordinates in the game for a number
	// I calculated the distance between the two coordinates.
	distance1 = abs(x - block_x) + abs(y - block_y);
	distance2 = abs(x - empty_x) + abs(y - empty_y);
	return distance1-distance2;	
}

void NPuzzle::Board::findCurrentNumber(string block, string& number){
	int num1 = 50, num2 = 49;
	string currentNumber = "01";

	auto i = 0;
	while( i < row*column-1-wall_number ){
		if(block == currentNumber)	number = currentNumber; // I am trying to find the current number in the block, increasing the value of number according to the numbers in the game.
		// I make this increase according to the ascii table.
		if(num1 > 57){
			num1 = 48;
			currentNumber[0] = num2;
			num2++;
		}
		currentNumber[1] = num1;
		num1++;
		i++;
	}
}

void NPuzzle::Board::findTrueCoordinates(string block, int& x, int& y){
	string numbers[row*column];
	int i, j;

	fillFinalBoard(numbers);
	auto k = 0;
	for(i=0; i<row; i++){ // I found the correct coordinates for the number.
		for(j=0; j<column; j++){
			if(board[i][j] != "00"){
				if(block == numbers[k]){
					x = i;
					y = j;
				}
				k++;
			}
		}
	}
}

void NPuzzle::Board::accessSize(int& size1, int& size2) const{
	size1 = row;
	size2 = column;
}

bool NPuzzle::shuffle(int N){
	reset();
	moveRandom(N);
	return gameBoard.isSolved();
};

void NPuzzle::moveRandom(int numberOfMoves){
	int random_move;
	bool flag;
	auto counter = 0;
	while(counter < numberOfMoves){
		random_move = rand() % 4; // for Left, Right, Up, Down
		switch(random_move){
			case 0: //LEFT
				if(previous_move != 1){
					move('L', flag);
					if(flag != false)	cout << "Random move is: L" << endl;
				}
				else	flag = false;
			break;
			case 1: //RIGHT
				if(previous_move != 0){
					move('R', flag);
					if(flag != false)	cout << "Random move is: R" << endl;
				}
				else	flag = false;
			break;
			case 2: //UP
				if(previous_move != 3){
					move('U', flag);	
					if(flag != false)	cout << "Random move is: U" << endl;
				}
				else	flag = false;
			break;
			case 3: //DOWN
				if(previous_move != 2){
					move('D', flag);
					if(flag != false)	cout << "Random move is: D" << endl;
				}
				else	flag = false;
			break;
		}
		if(flag != false){
			print();
			counter++;
			previous_move = random_move;
		}
	}
}

void NPuzzle::reset(){
	gameBoard.reset();
}

void NPuzzle::Board::reset(){
	string numbers[row*column];
	int i, j;

	fillFinalBoard(numbers);

	auto k = 0;
	for(i=0; i<row; i++){ // I filled the board with the numbers in the array(numbers).
		for(j=0; j<column; j++){
			if(board[i][j] != "00"){
				board[i][j] = numbers[k];
				k++;
			}
		}
	}
	cout << "The final board is:" << endl;
	print();
}

void NPuzzle::writeToFile(){
	gameBoard.writeToFile();
}

void NPuzzle::Board::writeToFile(){
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

void NPuzzle::readFromFile(string file_name){
	gameBoard.readFromFile(file_name);
	previous_move = 2;
}

void NPuzzle::Board::readFromFile(string file_name){ // this function reads the file.
	row = 0, column = 0;
	string line;
	bool flag;

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
		row++; // the number of row
	
	int i = 0;
	while(i < 25){
			if(line[i] == ' ')	column++; // the number of column
			i++;
	}
	column += 1;
	gameBoard.close();

	int x = 0, y = 0;
	gameBoard.open(file_name);
	while(gameBoard >> board[x][y]){
		y++;
		if(y % column == 0){ // when reaches the end of the line, the number of rows increases.
			y = 0;
			x++;
		}
	}
	gameBoard.close();

	calculateWallNumber(); // this function calculates the number of wall in the game.
}

bool NPuzzle::move(char choice, bool& flag){
	if(choice == 'L' || choice == 'l')	previous_move = 0;
	if(choice == 'R' || choice == 'r')	previous_move = 1;
	if(choice == 'U' || choice == 'u')	previous_move = 2;
	if(choice == 'D' || choice == 'd')	previous_move = 3;
	gameBoard.move(choice, flag);
	return gameBoard.isSolved();
}

void NPuzzle::Board::move(char choice, bool& flag){
	flag = false;// if the empty cell do not move, the flag is false.
	findEmptyCell();
	switch(choice){
		case 'L':	case 'l':	//LEFT
			if(empty_y > 0){
				flag = true;
				if(movement(empty_x, empty_y-1) == false)	flag = false;
			}
		break;

		case 'R':	case 'r':	//RIGHT
			if(empty_y < column-1){
				flag = true;
				if(movement(empty_x, empty_y+1) == false)	flag = false;
			}
		break;

		case 'U':	case 'u':	//UP
			if(empty_x > 0){
				flag = true;
				if(movement(empty_x-1, empty_y) == false)	flag = false;
			}
		break;

		case 'D':	case 'd':	//DOWN
			if(empty_x < row-1){
				flag = true;
				if(movement(empty_x+1, empty_y) == false)	flag = false;
			}
		break;
	}
}

void NPuzzle::Board::findEmptyCell(){ // this function find the empty cell's current coordinates.
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

bool NPuzzle::Board::movement(int x, int y){ // this function swaps the two coordinates.
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

bool NPuzzle::Board::isSolved(){
	string numbers[row*column];
	int i, j, num1 = 50, num2 = 49;
	string number = "01";

	fillFinalBoard(numbers);//this function fills the array accordig to the final board.

	int k = 0;
	for(i=0; i<row; i++){
		for(j=0; j<column; j++){
			if(board[i][j] != "00"){
				if( board[i][j] !=  numbers[k] )	return false;
				k++;
			}
		}
	}
	return true;
}

void NPuzzle::printReport(int counter){
	cout << "Total number of moves " << counter << endl;
	if(gameBoard.isSolved() == true)	cout << "This game is solved!" << endl << endl;
	else 	cout << "This game is not solved yet!" << endl << endl;
}

void NPuzzle::Board::calculateWallNumber(){ // this function calculates the number of wall in the game.
	int i, j;
	wall_number = 0;

	for(i=0; i<row; i++){
		for(j=0; j<column; j++){
			if(board[i][j] == "00") wall_number++;
		}
	}
}

void NPuzzle::Board::fillFinalBoard(string numbers[]){ //this function fills the array accordig to the final board.
	int i, j, num1 = 50, num2 = 49;
	string number = "01";

	for(i=0; i<row*column-1-wall_number; i++){ // I filled the array with the numbers in the game with using ascii table. I used the array to compare the correct board with the current board and fill the final board. 
		numbers[i] = number;
		if(num1 > 57){
			num1 = 48;
			number[0] = num2;
			num2++;
		}
		number[1] = num1;
		num1++;
	}
	numbers[row*column-1-wall_number] = "bb"; // I put 0 on the last element of the array for the empty cell.
}

void NPuzzle::print(){
	gameBoard.print();
}

void NPuzzle::Board::print(){
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
}

void NPuzzle::setSize(){
	gameBoard.setSize();
	previous_move = 2; 
}

void NPuzzle::Board::setSize(){
	cout << "Please enter the row and column for game board: ";
	cin >> row >> column;
	initRandomBoard();// I fill the game board in this function.
	calculateWallNumber(); // this function calculates the number of wall in the game.
}

void NPuzzle::Board::initRandomBoard(){ // I fill the game board in this function. 
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
}