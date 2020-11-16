#include<iostream>
#include<string>
#include<ctime>
#include<cstdlib>
#include<fstream>

using namespace std;

void readFile(string board[][9], const int size2, string file_name); // This function reads the file.
inline void findSize(int& size1, int& size2, string file_name); // This function find the size of the board in the file.
void print_board(string board[][9], const int size1, const int size2);
void movement(string board[][9], int x1, int y1, int x2, int y2); // this function swaps the two coordinates.
void findEmptyCell(string board[][9], const int size1, const int size2, int& empty_x, int& empty_y); // this function finds the empty cell's coordinates.
void menu(string board[][9], int size1, int size2);
int controlBoard(string board[][9], const int size1, const int size2);  // This function how many numbers are in the correct location.
void intelligentMove(string board[][9], const int size1, const int size2, int empty_x, int empty_y);
void twoBlockMove(string board[][9], const int size1, const int size2, int empty_x, int empty_y, int x1, int y1, int x2, int y2); // this function is for blocks with two blocks around it. (for corners)
int findDistance(string board[][9], const int size1, const int size2, int empty_x,int empty_y, int block_x, int block_y); // this function calculates the distance between the two coordinates. I also decided to move the block according to the difference between distances.
void findCurrentNumber(string board[][9], string block, const int size1, const int size2, string& number);  // this function finds the number in the current block
void findTrueCoordinates(string board[][9], string block,const int size1, const int size2, int& x, int& y);  // this function finds the correct coordinates in the game for a number
void threeBlockMove(string board[][9], const int size1, const int size2, int empty_x, int empty_y, int x1, int y1, int x2, int y2, int x3, int y3);
void fourBlockMove(string board[][9], const int size1, const int size2, int empty_x, int empty_y, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4);
void solveBoard(string board[][9], const int size1, const int size2, int& counter);
void saveBoard(string board[][9], const int size1, const int size2);
void loadBoard(string board[][9], int& size1, int& size2);
void shuffleMove(string board[][9], const int size1, const int size2);
void randomBoard(string board[][9], const int size1, const int size2); // I fill the game board in this function. 
bool control_elements(int element, int k, int array[]); // this function checks if the random number is in the board.
int calculate_wall_number(string board[][9], const int size1, const int size2); // this function calculates the number of wall in the game.
void fillFinalBoard(string Board[][9], const int size1, const int size2, string numbers[]); //this function fills the array accordig to the final board.
bool randomMove(string board[][9], const int size1, const int size2, int random);

int main(int argc, char *argv[]){
	string board[9][9];
	int size1;
	decltype(size1) size2; // these variables are the board size.
	auto counter = 1/*number of moves*/;
	
	size1 = 0, size2 = 0;

	if(argc == 1){ // random board
		cout << "Please enter two size for your random game board: " << endl;
		cin >> size1 >> size2;
		randomBoard(board, size1, size2);
	}
	else if(argc == 2){ // board in the file
		findSize(size1, size2, *(argv+1));
		readFile(board, size2, *(argv+1));
	}

	cout << "Your initial random board is" << endl;
	print_board(board, size1, size2);
	cout << endl;

	menu(board, size1, size2);

	return 0;
}

void randomBoard(string board[][9],const int size1,const int size2){ // I fill the game board in this function. 
	int temp[9][9], control_array[size1*size2], i, j;
	bool flag;
	int count = 0;

	//fill the board
	for(i=0; i<size1; i++){
		for(j=0; j<size2; j++){
			do{
				temp[i][j] = rand() % (size1*size2);
				flag = control_elements(temp[i][j], count, control_array); // this function checks if the random number is in the board. when the random number exists in the array, flag is false.
			}while(flag != true);
			control_array[count] = temp[i][j];
			count++;
		}
	}

	string number[size1*size2];
	int k = 0;
	//I convert integer array to string array.
	for(i=0; i<size1; i++){
		for(j=0; j<size2; j++){
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

inline void findSize(int& size1, int& size2, string file_name){ // This function find the size of the board in the file.
	int i = 0;
	string line;

	fstream gameBoard;
	gameBoard.open(file_name.c_str());
	
	while( getline(gameBoard, line) )
		size1++; // the number of row
	
	while(i < 25){
			if(line[i] == ' ')	size2++; // the number of column
			i++;
	}
	size2 += 1;
	
	gameBoard.close();
}

void readFile(string board[][9],const int size2, string file_name){ // this function reads the file.
	int x = 0, y = 0;

	fstream gameBoard;

	gameBoard.open(file_name);
	while(gameBoard >> board[x][y]){
		y++;
		if(y % size2 == 0){ // when reaches the end of the line, the number of rows increases.
			y = 0;
			x++;
		}
	}
	gameBoard.close();
}

bool control_elements(int element, int count, int array[]){ // this function checks if the random number is in the board.
	int i, counter = 0;
	bool flag;

	for(i=0; i<count; i++){
		if(element == array[i]) counter++; // if the random number exists in the array, this counter increases. so flag is false.
	}

	if(counter == 0)	flag = true;
	else	flag = false;

	return flag;
}

void menu(string board[][9], int size1, int size2){

	int x, y, counter = 1 /*number of moves*/;
	char choice , quit = 's';
	int control, i, j;
	int option;

	cout << "----------------------------------------------------------------------------------------------------------------------" << endl;
	cout << "(L) moves the empty cell left if there is room" << endl;
	cout << "(R) moves the empty cell right if there is room" << endl;
	cout << "(U) moves the empty cell up if there is room" << endl;
	cout << "(D) moves the empty cell down if there is room" << endl;
	cout << "(I) Intelligent move moves the blank tile in a way that after the move, the tiles are closer to their final positions." << endl;
	cout << "(S) Shuffle- takes the board to the final solution, and makes size*size random moves to shuffle the board." << endl;
	cout << "(V) Solves the puzzle." << endl;
	cout << "(T) Prints a report about how many moves have been done and if the solution is found." << endl;
	cout << "(E) Enter a file name for saves the current board configuration as a loadable shape file." << endl;
	cout << "(Y) Enter a file name and loads the current board configuration from the shape file." << endl;
	cout << "(Q) Quits the game" << endl;
	cout << "----------------------------------------------------------------------------------------------------------------------" << endl << endl;

	auto wall_number = calculate_wall_number(board, size1, size2);

	while(control != size1*size2 - wall_number && choice != 'Q'){
		cout << "Your move: ";
		cin >> choice;
		findEmptyCell(board, size1, size2, x, y);
		switch(choice){
			case 'L': //LEFT
			case 'l':
				if(y > 0)	movement(board, x, y, x, y-1);	
				else	cout << "The empty cell cannot move. Please try again." << endl << endl;
			break;

			case 'R': //RIGHT
			case 'r':
				if(y < size2-1)	movement(board, x, y, x, y+1);	
				else	cout << "The empty cell cannot move. Please try again." << endl << endl;
			break;

			case 'U': //UP
			case 'u':
				if(x > 0)	movement(board, x, y, x-1, y);	
				else	cout << "The empty cell cannot move. Please try again." << endl;
			break;

			case 'D': //DOWN
			case 'd':
				if(x < size1-1)	movement(board, x, y, x+1, y);	
				else	cout << "The empty cell cannot move. Please try again." << endl;
			break;

			case 'I': //INTELLIGENT
			case 'i':
				intelligentMove(board, size1, size2, x, y);
			break;

			case 'S': //SHUFFLE
			case 's':
				shuffleMove(board, size1, size2);
			break;

			case 'Q': //QUIT
			case 'q':
				cout << "You are exiting.." << endl;
				quit = 'q';
			break;
	
			case 'V': //SOLVE
			case 'v':
				solveBoard(board, size1, size2, counter);
				counter--;
			break;

			case 'T': //PRINT REPORT
			case 't':
				counter--;
				cout << "Total number of moves " << counter << endl << endl;
			break;
				
			case 'E': //SAVE SHAPE FILE
			case 'e':
				saveBoard(board, size1, size2);
				counter--;
			break;

			case 'Y': //LOAD SHAPE FILE
			case 'y':
				size1 = 0, size2 = 0;
				loadBoard(board, size1, size2);
				wall_number = calculate_wall_number(board, size1, size2);
				counter = 0;
			break;
	
			default: cout << "This is invalid choice!" << endl;
		} //end of switch

		if( quit != 'q' ){
			cout << "Your new board is: " << endl;
			print_board(board, size1, size2);
		}

		cout << endl;
		cout << "Total number of moves " << counter << endl << endl;
		counter++;
		control = controlBoard(board, size1, size2); // this function checks the numbers location.
		if(control == size1*size2 - wall_number)	cout << "Problem Solved!" << endl;

	}//end of while
}

void print_board(string board[][9],const int size1,const int size2){
	int i, j;

	cout << endl;
	for(i=0; i<size1; i++){
		for(j=0; j<size2; j++){
			cout.width(5);
			if(board[i][j] == "bb")	cout << " ";
			else if(board[i][j] == "00")	cout << "*";
			else	cout << board[i][j];
		}
		cout << endl;
	}
}

void findEmptyCell(string board[][9],const int size1,const int size2, int& empty_x, int& empty_y){ // this function finds the empty cell's coordinates.
	int i, j;

	for(i=0; i<size1; i++){
		for(j=0; j<size2; j++){
			if(board[i][j] == "bb"){
				empty_x = i;
				empty_y = j;
			}
		}
	}
}

void movement(string board[][9], int x1, int y1, int x2, int y2){ // this function swaps the two coordinates.
	string temp;

	if(board[x1][y1] != "00" && board[x2][y2] != "00"){
		temp = board[x2][y2];
		board[x2][y2] = board[x1][y1];
		board[x1][y1] = temp;
	}
	else	cout << "You cannot move! This is impossible position." << endl << endl;
}

void intelligentMove(string board[][9],const int size1,const int size2, int empty_x, int empty_y){
	// In this function I determine the numbers around the empty cell and calculate the distance between these number and these numbers's correct position in the game.
	int temp_x, temp_y;
	int previous_empty_x = empty_x, previous_empty_y = empty_y; // I use these variables for empty cell's previous coordinates. I determine the direction of movement according to the difference between these coordinates.

	if(empty_y == 0){ // first column 
		if(empty_x == 0){ // (0,0)
			twoBlockMove(board, size1, size2, empty_x, empty_y, 0, 1, 1, 0);			
		}
		else if(empty_x == size1-1){ // ( size1-1, 0)
			twoBlockMove(board, size1, size2, empty_x, empty_y, size1-2, 0, size1-1, 1);
		}
		else{ // (  , 0) for edges
			for(temp_x=1; temp_x<size1-1; temp_x++){
				if(empty_x == temp_x)
					threeBlockMove(board, size1, size2, empty_x, empty_y, temp_x+1, 0, temp_x-1, 0, temp_x, 1);
			}
		}
	}
	else if(empty_y == size2-1){ // last column
		if(empty_x == 0){ // ( 0, size2-1)
			twoBlockMove(board, size1, size2, empty_x, empty_y, 0, size2-2, 1, size2-1);
		}
		else if(empty_x == size1-1){ // ( size1-1, size2-1)
			twoBlockMove(board, size1, size2, empty_x, empty_y, size1-1, size2-2, size1-2, size2-1);
		}
		else{ // (  , size2-1) for edges
			for(temp_x=1; temp_x<size1-1; temp_x++){
				if(empty_x == temp_x)
					threeBlockMove(board, size1, size2, empty_x, empty_y, temp_x+1, size2-1, temp_x-1, size2-1, temp_x, size2-2);
			}
		}
	}
	else if(empty_x == 0){ // first row
		// (0, 0)
		// ( 0, size2-1)
		if(empty_y != 0 && empty_y != size2-1){ // ( 0,  ) for edges
			for(temp_y=1; temp_y<size2-1; temp_y++){
				if(empty_y == temp_y)
					threeBlockMove(board, size1, size2, empty_x, empty_y, 0, temp_y-1, 0, temp_y+1, 1, temp_y);
			}
		}
	}
	else if(empty_x == size1-1){ //last row
		// ( size-1, 0)
		// ( size-1, size-1)
		if(empty_y != 0 && empty_y != size2-1) { // ( size-1,  ) for edges
			for(temp_y=1; temp_y<size2-1; temp_y++){
				if(empty_y == temp_y)
					threeBlockMove(board, size1, size2, empty_x, empty_y, size1-1, temp_y-1, size1-1, temp_y+1, size1-2, temp_y);
			}
		}
	}
	else{ // for middle sections
		for(temp_x=1; temp_x<=size1-2; temp_x++){	
			for(temp_y=1; temp_y<=size2-2; temp_y++){
				if(empty_y == temp_y && empty_x == temp_x)
					fourBlockMove(board, size1, size2, empty_x, empty_y, temp_x, temp_y-1, temp_x, temp_y+1, temp_x-1, temp_y, temp_x+1, temp_y);
			}
		}
	}
	
	findEmptyCell(board, size1, size2, empty_x, empty_y); // I found the empty cell's current coordinates
	// I determine the direction of movement based on the empty cell's coordinates.
	if(previous_empty_x - empty_x > 0 && previous_empty_x - empty_x != 0)
		cout <<  "Intelligent move chooses U" << endl;
	else if(previous_empty_x - empty_x != 0)	cout << "Intelligent move chooses D" << endl;

	if(previous_empty_y - empty_y > 0 && previous_empty_y - empty_y != 0)
		cout << "Intelligent move chooses L" << endl;
	else if(previous_empty_y - empty_y != 0)	cout << "Intelligent move chooses R"  << endl;
}

void twoBlockMove(string board[][9],const int size1,const int size2, int empty_x, int empty_y, int x1, int y1, int x2, int y2){ // this function is for blocks with two blocks around it. (for corners)
	int distance1, distance2;
	bool flag = false;

	distance1 = findDistance(board, size1, size2, empty_x, empty_y, x1, y1);
	distance2 = findDistance(board, size1, size2, empty_x, empty_y, x2, y2);
	// If all number are positive, the smaller one moves.	
	if(distance1 > 0 && distance2 < 0 && board[x1][y1] != "00"){
		movement(board, x1, y1, empty_x, empty_y);
		flag = true;

	}
	else if(distance1 < 0 && distance2 > 0 && board[x2][y2] != "00"){
		movement(board, x2, y2, empty_x, empty_y);
		flag = true;

	}
	else if(board[x1][y1] != "00" && board[x2][y2] != "00"){ // distance1 and distance2 are negative numbers(if the distance is negative, the number moves away from the corrrect position.), so I found the positive values for them and I chose to move the big one.
		distance1 = abs(distance1);
		distance2 = abs(distance2);

		if(distance1 > distance2) movement(board, x1, y1, empty_x, empty_y);
		else	movement(board, x2, y2, empty_x, empty_y);
		flag = true;

	}
	if(flag == false){
		if(board[x1][y1] != "00") movement(board, x1, y1, empty_x, empty_y);
		else if(board[x2][y2] != "00")	movement(board, x2, y2, empty_x, empty_y);
	}
}

int findDistance(string board[][9],const int size1,const int size2, int empty_x,int empty_y, int block_x, int block_y){ // this function calculates the distance between the two coordinates. I also decided to move the block according to the difference between distances.
	int distance1, distance2, x, y;
	string number;

	findCurrentNumber(board, board[block_x][block_y], size1, size2, number); // this function finds the number in the current block
	findTrueCoordinates(board, number, size1, size2, x, y); // this function finds the correct coordinates in the game for a number
	// I calculated the distance between the two coordinates.
	distance1 = abs(x - block_x) + abs(y - block_y);
	distance2 = abs(x - empty_x) + abs(y - empty_y);

	return distance1-distance2;	
}

void findCurrentNumber(string board[][9], string block,const int size1,const int size2, string& number){ // this function finds the number in the current block.
	int i, num1 = 50, num2 = 49;
	string currentNumber = "01";

	auto wall_number = calculate_wall_number(board, size1, size2);

	i = 0;
	while( i < size1*size2-1-wall_number ){
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

int calculate_wall_number(string board[][9],const int size1,const int size2){ // this function calculates the number of wall in the game.
	int i, j, number_of_wall = 0;

	for(i=0; i<size1; i++){
		for(j=0; j<size2; j++){
			if(board[i][j] == "00") number_of_wall++;
		}
	}
	return number_of_wall;
}

void fillFinalBoard(string board[][9],const int size1,const int size2, string numbers[]){ //this function fills the array accordig to the final board.
	int i, j, num1 = 50, num2 = 49;
	string number = "01";

	int wall_number = calculate_wall_number(board, size1, size2);

	for(i=0; i<size1*size2-1-wall_number; i++){ // I filled the array with the numbers in the game with using ascii table. I used the array to compare the correct board with the current board and fill the final board. 
		numbers[i] = number;
		if(num1 > 57){
			num1 = 48;
			number[0] = num2;
			num2++;
		}
		number[1] = num1;
		num1++;
	}
	numbers[size1*size2-1-wall_number] = "bb"; // I put 0 on the last element of the array for the empty cell.
}

void findTrueCoordinates(string board[][9], string block,const int size1,const int size2, int& x, int& y){ // this function finds the correct coordinates in the game for a number.
	string numbers[size1*size2];
	int i, j;

	fillFinalBoard(board, size1, size2, numbers);

	int k = 0;
	for(i=0; i<size1; i++){ // I found the correct coordinates for the number.
		for(j=0; j<size2; j++){
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

void threeBlockMove(string board[][9],const int size1,const int size2, int empty_x, int empty_y, int x1, int y1, int x2, int y2, int x3, int y3){ // this function is for blocks with three blocks around it. (for edges)
	int distance1, distance2, distance3;
	bool flag = false;

	distance1 = findDistance(board, size1, size2, empty_x, empty_y, x1, y1);
	distance2 = findDistance(board, size1, size2, empty_x, empty_y, x2, y2);
	distance3 = findDistance(board, size1, size2, empty_x, empty_y, x3, y3);
	// If all number are positive, the smaller one moves.		
	if(distance1 >= 0){ // 1 --- positive
		if(distance2 >= 0){ // 2 --- positive
			if(distance3 >= 0){ // 3 --- positive
				if(distance1 <= distance2 && distance1 <= distance3 && board[x1][y1] != "00"){
					movement(board, x1, y1, empty_x, empty_y);
					flag = true;
				}
				else if(distance2 <= distance1 && distance2 <= distance3 && board[x2][y2] != "00"){
					movement(board, x2, y2, empty_x, empty_y);
					flag = true;
				}
				else if(distance3 <= distance1 && distance3 <= distance2 && board[x3][y3] != "00"){
					movement(board, x3, y3, empty_x, empty_y);
					flag = true;
				}
			}
			else{ // 3 --- negative
				if(distance1 < distance2 && board[x1][y1] != "00"){
					movement(board, x1, y1, empty_x, empty_y);
					flag = true;
				}
				else if(board[x2][y2] != "00"){
					movement(board, x2, y2, empty_x, empty_y);
					flag = true;
				}
			}
		}
		else{ // 2 --- negative
			if(distance3 >= 0){ // 3 --- positive
				if(distance1 < distance3 && board[x1][y1] != "00"){
					movement(board, x1, y1, empty_x, empty_y);
					flag = true;
				}
				else if(board[x3][y3] != "00"){
					movement(board, x3, y3, empty_x, empty_y);
					flag = true;
				}
			}
			else if(board[x1][y1] != "00"){
				movement(board, x1, y1, empty_x, empty_y); // 3 --- negative
				flag = true;
			}
		}
	}
	else{ // distance1 < 0
		if(distance2 >= 0){ // 2 --- positive
			if(distance3 >= 0){ // 3 --- positive
				if(distance2 < distance3 && board[x2][y2] != "00"){
					movement(board, x2, y2, empty_x, empty_y);
					flag = true;
				}
				else if(board[x3][y3] != "00"){
					movement(board, x3, y3, empty_x, empty_y);
					flag = true;
				}
			}
			else if(board[x2][y2] != "00"){
					movement(board, x2, y2, empty_x, empty_y);  // 3 --- negative
					flag = true;
			}
		}
		else{ // 2 --- negative
			if(distance3 >= 0 && board[x3][y3] != "00"){
				movement(board, x3, y3, empty_x, empty_y); // 3 --- positive
				flag = true;
			}
			else if(board[x1][y1] != "00" && board[x2][y2] != "00" && board[x3][y3] != "00"){ // 3 --- negative 
			// distance1, distance2 and distance3 are negative numbers(if the distance is negative, the number moves away from the corrrect position.), so I found the positive values for them and I chose to move the big one.
				distance1 = abs(distance1);
				distance2 = abs(distance2);
				distance3 = abs(distance3);

				if(distance1 >= distance2 && distance1 >= distance3) movement(board, x1, y1, empty_x, empty_y);
				else if(distance2 >= distance1 && distance2 >= distance3) movement(board, x2, y2, empty_x, empty_y);
				else if(distance3 >= distance1 && distance3 >= distance2)	movement(board, x3, y3, empty_x, empty_y);
				flag = true;
			}
		}
	}
	if(flag != true){
		if(board[x1][y1] != "00") movement(board, x1, y1, empty_x, empty_y);
		else if(board[x2][y2] != "00")	movement(board, x2, y2, empty_x, empty_y);
		else if(board[x3][y3] != "00")	movement(board, x3, y3, empty_x, empty_y);

	}
}

void fourBlockMove(string board[][9],const int size1,const int size2, int empty_x, int empty_y, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4){ // this function is for blocks with four blocks around it. (for middle sections)
	int distance1, distance2, distance3, distance4;
	bool flag = false;

	distance1 = findDistance(board, size1, size2, empty_x, empty_y, x1, y1);
	distance2 = findDistance(board, size1, size2, empty_x, empty_y, x2, y2);
	distance3 = findDistance(board, size1, size2, empty_x, empty_y, x3, y3);
	distance4 = findDistance(board, size1, size2, empty_x, empty_y, x4, y4);
	// If all number are positive, the smaller one moves.		
	if(distance1 >= 0){  // distance1 positive
		if(distance2 >= 0){ // distance2 positive (distance1 positive)
			if(distance3 >= 0){ // distance3 positive (distance1 , distance2 positive)
				if(distance4 >= 0){ // distance4 positive (1, 2, 3, 4 positive)
					if(distance1 <= distance2 && distance1 <= distance3 && distance1 <= distance4 && board[x1][y1] != "00"){
						movement(board, x1, y1, empty_x, empty_y);
						flag = true;
					}
					else if(distance2 <= distance1 && distance2 <= distance3 && distance2 <= distance4 && board[x2][y2] != "00"){
						movement(board, x2, y2, empty_x, empty_y);
						flag = true;
					}
					else if(distance3 <= distance1 && distance3 <= distance2 && distance3 <= distance4 && board[x3][y3] != "00"){
						movement(board, x3, y3, empty_x, empty_y);
						flag = true;
					}
					else if(distance4 <= distance1 && distance4 <= distance2 && distance4 <= distance3 && board[x4][y4] != "00"){
						movement(board, x4, y4, empty_x, empty_y);
						flag = true;
					}
				}
				else{ // distance4 negative (1, 2, 3 positive)
					if(distance1 <= distance2 && distance1 <= distance3  && board[x1][y1] != "00"){
						movement(board, x1, y1, empty_x, empty_y);
						flag = true;
					}
					else if(distance2 <= distance1 && distance2 <= distance3 && board[x2][y2] != "00"){
						movement(board, x2, y2, empty_x, empty_y);
						flag = true;
					}
					else if(distance3 <= distance1 && distance3 <= distance2 && board[x3][y3] != "00"){
						movement(board, x3, y3, empty_x, empty_y);
						flag = true;
					}
				}
			}
			else{ // distance3 negative (distance1 , distance2 positive)
				if(distance4 >= 0){ // distance4 positive (1, 2, 4 positive)
					if(distance1 <= distance2 && distance1 <= distance4 && board[x1][y1] != "00"){
						movement(board, x1, y1, empty_x, empty_y);
						flag = true;
					}
					else if(distance2 <= distance1 && distance2 <= distance4 && board[x2][y2] != "00"){
						movement(board, x2, y2, empty_x, empty_y);
						flag = true;
					}
					else if(distance4 <= distance1 && distance4 <= distance2 && board[x4][y4] != "00"){
						movement(board, x4, y4, empty_x, empty_y);
						flag = true;
					}
				}
				else{ // distance4 negative (1, 2 positive)
					if(distance1 < distance2 && board[x1][y1] != "00"){
						movement(board, x1, y1, empty_x, empty_y);
						flag = true;
					}
					else if(board[x2][y2] != "00"){
						movement(board, x2, y2, empty_x, empty_y);
						flag = true;
					}
				}
			}
		}
		else{ // distance2 negative
			if(distance3 >= 0){ // distance3 positive (distance1 positive, distance2 negative)
				if(distance4 >= 0){ // distance4 positive (1, 3, 4 positive)
					if(distance1 <= distance3 && distance1 <= distance4 && board[x1][y1] != "00"){
						movement(board, x1, y1, empty_x, empty_y);
						flag = true;
					}
					else if(distance3 <= distance1 && distance3 <= distance4 && board[x3][y3] != "00"){
						movement(board, x3, y3, empty_x, empty_y);
						flag = true;
					}
					else if(distance4 <= distance1 && distance4 <= distance3 && board[x4][y4] != "00"){
						movement(board, x4, y4, empty_x, empty_y);
						flag = true;
					}
				}
				else{// distance4 negative (1, 3 positive)
					if(distance1 < distance3 && board[x1][y1] != "00"){
						movement(board, x1, y1, empty_x, empty_y);
						flag = true;
					}
					else if(board[x3][y3] != "00"){
						movement(board, x3, y3, empty_x, empty_y);
						flag = true;
					}
				}
			}
			else{ // distance3 negative (distance1 positive, distance2 negative)
				if(distance4 >= 0){ // distance4 positive (1, 4 positive)
					if(distance1 < distance4 && board[x1][y1] != "00"){
						movement(board, x1, y1, empty_x, empty_y);
						flag = true;
					}
					else if(board[x4][y4] != "00"){
						movement(board, x4, y4, empty_x, empty_y);
						flag = true;
					}
				}
				else if(board[x1][y1] != "00"){ // distance4 negative ( 1 positive)
					movement(board, x1, y1, empty_x, empty_y);
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
						movement(board, x2, y2, empty_x, empty_y);
						flag = true;
					}
					else if(distance3 <= distance2 && distance3 <= distance4 && board[x3][y3] != "00"){
						movement(board, x3, y3, empty_x, empty_y);
						flag = true;
					}
					else if(distance4 <= distance2 && distance4 <= distance3 && board[x4][y4] != "00"){
						movement(board, x4, y4, empty_x, empty_y);
						flag = true;
					}
				}
				else{ // distance4 negative (2, 3 positive)
					if(distance2 < distance3 && board[x2][y2] != "00"){
						movement(board, x2, y2, empty_x, empty_y);
						flag = true;
					}
					else if(board[x3][y3] != "00"){
						movement(board, x3, y3, empty_x, empty_y);
						flag = true;
					}
				}
			}
			else{ // distance3 negative (distance1 negative, distance2 positive)
				if(distance4 >= 0){ // (2, 4 positive)
					if(distance2 < distance4 && board[x2][y2] != "00"){
						movement(board, x2, y2, empty_x, empty_y);
						flag = true;
					}
					else if(board[x4][y4] != "00"){
						movement(board, x4, y4, empty_x, empty_y);
						flag = true;
					}
				}
				else if(board[x2][y2] != "00"){ // distance4 negative (2 positive)
					movement(board, x2, y2, empty_x, empty_y);
					flag = true;
				}
			}
		}
		else{ // distance2 negative
			if(distance3 >= 0){ // distance3 positive (distance1, distance2 negative)
				if(distance4 >= 0){ // (3, 4 positive)
					if(distance3 < distance4 && board[x3][y3] != "00"){
						movement(board, x3, y3, empty_x, empty_y);
						flag = true;
					}
					else if(board[x4][y4] != "00"){
						movement(board, x4, y4, empty_x, empty_y);
						flag = true;
					}
				}
				else if(board[x3][y3] != "00"){ // distance4 negative (3 positive)
					movement(board, x3, y3, empty_x, empty_y);
					flag = true;
				}
			}
			else{ // distance3 negative (distance1, distance2 negative)
				if(distance4 >= 0  && board[x4][y4] != "00"){ // (4 positive)
					movement(board, x4, y4, empty_x, empty_y);
					flag = true;
				}
				else if(board[x1][y1] != "00" && board[x2][y2] != "00" && board[x3][y3] != "00" && board[x4][y4] != "00"){ // distance4 negative (1, 2, 3, 4 negative)
				// distance1, distance2 and distance3 are negative numbers(if the distance is negative, the number moves away from the corrrect position.), so I found the positive values for them and I chose to move the big one.
					distance1 = abs(distance1);
					distance2 = abs(distance2);
					distance3 = abs(distance3);
					distance4 = abs(distance4);

					if(distance1 >= distance2 && distance1 >= distance3 && distance1 >= distance4) movement(board, x1, y1, empty_x, empty_y);
					else if(distance2 >= distance1 && distance2 >= distance3 && distance2 >= distance4) movement(board, x2, y2, empty_x, empty_y);
					else if(distance3 >= distance1 && distance3 >= distance2 && distance3 >= distance4)	movement(board, x3, y3, empty_x, empty_y);
					else if(distance4 >= distance1 && distance4 >= distance2 && distance4 >= distance3)	movement(board, x4, y4, empty_x, empty_y);
					flag = true;
				}
			}
		}
	}
	if(flag != true){
		if(board[x1][y1] != "00") movement(board, x1, y1, empty_x, empty_y);
		else if(board[x2][y2] != "00")	movement(board, x2, y2, empty_x, empty_y);
		else if(board[x3][y3] != "00") movement(board, x3, y3, empty_x, empty_y);
		else if(board[x4][y4] != "00")	movement(board, x4, y4, empty_x, empty_y);
	}
}

void shuffleMove(string board[][9],const int size1,const int size2){
	string numbers[size1*size2];
	int i, j;

	fillFinalBoard(board, size1, size2, numbers);

	int k = 0;
	for(i=0; i<size1; i++){ // I filled the board with the numbers in the array(numbers).
		for(j=0; j<size2; j++){
			if(board[i][j] != "00"){
				board[i][j] = numbers[k];
				k++;
			}
		}
	}

	cout << "The final board is:" << endl;
	print_board(board, size1, size2);

	int random_move;
	int x, y /*these variables for empty cell's coordinates*/;
	bool flag /*this variable checks whether moves are made*/;
	k = 1;
	while(k < size1*size2){
		
		random_move = rand() % 4; // for Left, Right, Up, Down
		flag = randomMove(board, size1, size2, random_move);
		if(flag == true){ 
			k++; // The counter increases if move is made.(if the flag equals one)		
			print_board(board, size1, size2);
		}
	}
}

bool randomMove(string board[][9],const int size1,const int size2, int random){
	int x, y;
	bool flag;
	findEmptyCell(board, size1, size2, x, y);
	switch(random){
		case 0: //LEFT
			if(y > 0 && board[x][y-1] != "00"){
				movement(board, x, y, x, y-1);
				flag = true;
				cout << "Random move is: L" << endl;
			}
			else	flag = false;
		break;
		case 1: //RIGHT
			if(y < size2-1 && board[x][y+1] != "00"){
				movement(board, x, y, x, y+1);	
				flag = true;
				cout << "Random move is: R" << endl;
			}
			else	flag = false;
		break;
		case 2: //UP
			if(x > 0 && board[x-1][y] != "00"){
				movement(board, x, y, x-1, y);	
				flag = true;
				cout << "Random move is: U" << endl;
			}
			else	flag = false;
		break;
		case 3: //DOWN
			if(x < size1-1 && board[x+1][y] != "00"){
				movement(board, x, y, x+1, y);
				flag = true;
				cout << "Random move is: D" << endl;
			}
			else	flag = false;
		break;
	}
	return flag;
}

void solveBoard(string board[][9],const int size1,const int size2, int& counter){
	int x, y /* x and y are the empty cell's coordinates*/, i, j, random_move;
	bool flag;
	int number_of_random = 4, number_of_intelligent = 5;

	auto wall_number = calculate_wall_number(board, size1,size2);
	while(controlBoard(board, size1, size2) != size1*size2 - wall_number){
		//random move
		i = 0;
		while(i<number_of_random && controlBoard(board, size1, size2) != size1*size2 - wall_number){
			random_move = rand() % 4; // for Left, Right, Up, Down
			flag = randomMove(board, size1, size2, random_move);
			if(flag == true){
				print_board(board, size1, size2);
				i++;
				cout << "Total number of moves(in V): " << counter << endl << endl;
				counter++;//this variable is the number of moves in the game.
				
			}
			if(controlBoard(board, size1, size2) == (size1*size2 - wall_number)- ( (size1*size2 - wall_number)/4 )){
				number_of_random = 3;
				number_of_intelligent = 4;
			}
		}
		//intelligent move
		i = 0;
		while(i<number_of_intelligent && controlBoard(board, size1, size2) != size1*size2 - wall_number){
			findEmptyCell(board, size1, size2, x, y);
			intelligentMove(board, size1, size2, x, y);
			print_board(board, size1, size2);
			i++;
			cout << endl;
			cout << "Total number of moves(in V): " << counter << endl << endl;
			counter++;//this variable is the number of moves in the game.
		}
	}
}

int controlBoard(string board[][9],const int size1,const int size2){ // This function how many numbers are in the correct location.
	string numbers[size1*size2];
	int i, j, count = 0;

	fillFinalBoard(board, size1, size2, numbers);

	int k = 0;
	for(i=0; i<size1; i++){
		for(j=0; j<size2; j++){
			if(board[i][j] != "00"){
				if(board[i][j] == numbers[k]) 	count++; 
				k++;
			}
		}
	}

	return count;
}

void saveBoard(string board[][9],const int size1,const int size2){
	string file_name;
	int i, j;

	cout << "Please enter the file name(.txt) you want to save: " << endl;
	cin >> file_name;
	
	ofstream saveBoard;
	
	saveBoard.open(file_name);
	
	for(i=0; i<size1; i++){
		for(j=0; j<size2; j++){
		saveBoard << board[i][j] << "   ";
		}
		saveBoard << endl;
	}
	
	saveBoard.close();
}

void loadBoard(string board[][9], int& size1, int& size2){
	string file_name;

	cout << "Please enter the file name(.txt) you want to load." << endl;
	cin >> file_name;

	findSize(size1, size2, file_name);

	readFile(board, size2, file_name);
}