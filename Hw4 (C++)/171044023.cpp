#include<iostream>
#include<vector>
#include<string>
#include<fstream>

using namespace std;

class NPuzzle{

private:
	class Board{
	public:
		void readFromFile(string);
		void calculateWallNumber();
		void print();
		void setSize(int, int);
		void initRandomBoard();
		void findEmptyCell();
		char lastMove();
		void writeToFile();
		bool isSolved();
		void fillFinalBoard(string []);
		void reset();
		void move(char);
		bool movement(int , int);
		void accessSize(int& , int&) const;
		int numberOfMoves(){ return number_of_moves; }
		int numberOfBoards(){ return number_of_boards; }
		void accessEmptyCell(int& , int&);
		bool finalBoard(vector<Board> , int);
		string operator()(int const x, int const y){
			return board[x][y];
		}
		friend bool operator ==(const Board& b1, const Board& b2){
			int i, j;
			if((b1.row == b2.row) && (b1.column == b2.column)){
				for(i=0; i<b1.row; i++){
					for(j=0; j<b1.column; j++){
						if(b1.board[i][j] != b2.board[i][j])	return false;
					}
				}
			}
			return true;
		}
	private:
		vector < vector<string> > board;
		char last_move;
		int number_of_moves;
		int number_of_boards;
		int row, column;
		int wall_number;
		int empty_x, empty_y;
	};
	
public:
	vector <Board> gameBoard;
	void readFromFile(string);
	void print();
	void setSize();
	void Menu();
	void writeToFile();
	bool shuffle(int N);
	void reset();
	void moveRandom(int N);
	bool move(char);
	void printReport();
	friend ostream& operator <<(ostream& output, NPuzzle& Puzzle);
	friend istream& operator >>(istream& input, NPuzzle& Puzzle);
	void accessSize(int& , int&) const;
	void solvePuzzle();
	void solveMove(vector<Board>& , char, int);
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
	cout << Puzzle;
	Puzzle.Menu();

	return 0;
}

void NPuzzle::Menu(){
	char choice , quit = 's';
	auto control = false; // I use this variable to check if the game is over.
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
	cout << "(S) Shuffle- takes the board to the final solution, and makes size1*size2 random moves to shuffle the board." << endl;
	cout << "(Q) Quits the game" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------" << endl << endl;

	do{
		cout << "Your move: ";
		cin >> choice;
		switch(choice){
			case 'V':	case 'v':	//SOLVE
				solvePuzzle();
			break;

			case 'T':	case 't':	//PRINT REPORT
				printReport();	
			break;

			case 'E':	case 'e':	//WRITE FILE
				writeToFile();
			break;

			case 'O':	case 'o':	//READ FILE
				cout << "Please enter the file name(.txt) you want to load." << endl;
				cin >> file_name;
				readFromFile(file_name);
			break;

			case 'L':	case 'l':	//LEFT
			case 'R':	case 'r':	//RIGHT
			case 'U':	case 'u':	//UP
			case 'D':	case 'd':	//DOWN
				control = move(choice);
			break;

			case 'S':	case 's':	//SHUFFLE
				gameBoard[0].accessSize(size1, size2);
				control = shuffle(size1*size2);
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
		printReport();	
	} while(control != true && quit != 'q');
}

bool NPuzzle::Board::finalBoard(vector<Board> temp, int counter){
	//this fuction checks if the boards I push back in the vector of Board object are soluiton.
	for(int i=0; i<counter+1; i++){
		if(temp[i].isSolved())	return true;
	}
	return false;
}

void NPuzzle::solveMove(vector<Board>& temp, char choice, int counter){
	int k = 0;
	char reverse; //I use this variable to undo the move.
	if(choice == 'L')	reverse = 'R';
	else if(choice == 'R')	reverse = 'L';
	else if(choice == 'U')	reverse = 'D';
	else if(choice == 'D')	reverse = 'U';	
	move(choice);
	// Before doing psuh back, I check if the same board is already in the vector.
	for(int i=0; i<counter; i++){
		if( !(temp[i] == gameBoard[0]) )	k++;
	}
	if(k == counter)	temp.push_back(gameBoard[0]);
	move(reverse);
}

void NPuzzle::solvePuzzle(){
	int empty_x, empty_y;
	int row, column;
	accessSize(row, column);
	vector < Board > temp;
	temp.push_back(gameBoard[0]);
	
	int counter = 0;
	//possible moves
		gameBoard[0].accessEmptyCell(empty_x, empty_y);	
		// RIGHT
		if(empty_y < column-1){
			counter++;
			solveMove(temp, 'R', counter);
		}	
		// UP
		if(empty_x > 0){
			counter++;
			solveMove(temp, 'U', counter);
		}
		// LEFT
		if(empty_y > 0){
			counter++;
			solveMove(temp, 'L', counter);
		}	
		// DOWN
		if(empty_x < row-1){
			counter++;
			solveMove(temp, 'D', counter);
		}
}

void NPuzzle::Board::accessEmptyCell(int& x, int& y){
	// this function allows me to access the empty cell's coordinates.
	findEmptyCell(); // this function find the empty cell's current coordinates.
	x = empty_x;
	y = empty_y;
}

ostream& operator <<(ostream& output, NPuzzle& Puzzle){
	int row, column;
	Puzzle.accessSize(row, column);
	
	for(int i=0; i<row; i++){
		for(int j=0; j<column; j++){
			output << Puzzle.gameBoard[0](i, j) << " ";
		}
		output << endl;
	}
	return output;
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

bool NPuzzle::move(char choice){
	gameBoard[0].move(choice);
	return gameBoard[0].isSolved();
}

void NPuzzle::Board::move(char choice){
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
		number_of_moves++;
		last_move = choice;
	}
}

bool NPuzzle::shuffle(int N){
	reset();
	moveRandom(N);
	return gameBoard[0].isSolved();
}

void NPuzzle::moveRandom(int N){
	int random_move;
	auto counter = 0;
	int num_moves;
	char choice;

	while(counter < N){
		num_moves = gameBoard[0].numberOfMoves();// the current number of moves
		random_move = rand() % 4; // for Left, Right, Up, Down
		switch(random_move){
			case 0: //LEFT
				if(gameBoard[0].lastMove() != 'R'){
					choice = 'L';
					move(choice);
				}
			break;
			case 1: //RIGHT
				if(gameBoard[0].lastMove() != 'L'){
					choice = 'R';
					move(choice);
				}
			break;
			case 2: //UP
				if(gameBoard[0].lastMove() != 'D'){
					choice = 'U';
					move(choice);
				}
			break;
			case 3: //DOWN
				if(gameBoard[0].lastMove() != 'U'){
					choice = 'D';
					move(choice);
				}
			break;
		}
		if(num_moves < gameBoard[0].numberOfMoves()){//if a move is made, this if runs.
			cout << "Random move is: " << choice;
			print();
			counter++;
		}
	}
}

void NPuzzle::reset(){
	int size1, size2;
	gameBoard[0].accessSize(size1, size2);//When I reset the board, I lose the value of the row and column. so I save them before reset.
	gameBoard.resize(0);
	gameBoard.resize(1);
	gameBoard[0].setSize(size1, size2);
	gameBoard[0].reset();
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
	number_of_moves = 0;
}

bool NPuzzle::Board::isSolved(){
	//this function checks if this board is solved.
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

void NPuzzle::writeToFile(){
	gameBoard[0].writeToFile();
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

char NPuzzle::Board::lastMove(){
	if(number_of_moves == 0)	return 'S';
	return last_move;
}

void NPuzzle::readFromFile(string file_name){
	gameBoard.resize(1);
	gameBoard[0].readFromFile(file_name);
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

	board.resize(row);
	for(int i=0; i<row; i++)
		board[i].resize(column);

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

	number_of_moves = 0;
	number_of_boards = 0;
	calculateWallNumber(); // this function calculates the number of wall in the game.
}

void NPuzzle::print(){
	gameBoard[0].print();
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
	cout << endl;
}

void NPuzzle::setSize(){
	int size1, size2;
	cout << "Please enter the row and column for game board: ";
	cin >> size1 >> size2;
	gameBoard.resize(1);
	gameBoard[0].setSize(size1, size2);
	gameBoard[0].initRandomBoard();// I fill the game board in this function.
}

void NPuzzle::Board::setSize(int size1, int size2){
	row = size1;
	column = size2;

	board.resize(row);
	for(int i=0; i<row; i++)
		board[i].resize(column);
	
	number_of_moves = 0;
	number_of_boards = 0;
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
	calculateWallNumber(); // this function calculates the number of wall in the game.
}

void NPuzzle::accessSize(int& size1, int& size2) const{
	gameBoard[0].accessSize(size1, size2);
}

void NPuzzle::printReport(){
	cout << "Total number of moves " << gameBoard[0].numberOfMoves() << endl;
	if(gameBoard[0].isSolved() == true)	cout << "This game is solved!" << endl << endl;
	else 	cout << "This game is not solved yet!" << endl << endl;
}

void NPuzzle::Board::accessSize(int& size1, int& size2) const{
	size1 = row;
	size2 = column;
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