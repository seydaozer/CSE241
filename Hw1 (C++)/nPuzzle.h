void menu();
void random_board(int board[][9], int size); // this function determines the elements of the board.
bool control_elements(int element, int k, int array[]); // this function checks if the random number is in the board.
void print_board(int board[][9], int size);
bool control_positions(int board[][9], int size); // This function checks the numbers location.
void find_empty_cell(int board[][9], int size, int& x, int& y); // this function finds the empty cell's coordinates.
void movement(int board[][9], int x1, int y1, int x2, int y2); // this function swaps the two coordinates.
void intelligent_move(int board[][9], int size, int x, int y);
int find_distance(int board[][9], int size, int empty_x,int empty_y, int block_x, int block_y); // this function calculates the distance between the two coordinates.
int find_current_number(int number, int size);  // this function finds the number in the current block.
void find_true_position(int number, int size, int& x, int& y); // this function finds the correct coordinates in the game for a number.
void two_locate_move(int board[][9], int size, int empty_x, int empty_y, int x1, int y1, int x2, int y2);// this function is for blocks with two blocks around it. (for corners)
void three_locate_move(int board[][9], int size, int empty_x, int empty_y, int x1, int y1, int x2, int y2, int x3, int y3); // this function is for blocks with three blocks around it. (for edges)
void four_locate_move(int board[][9], int size, int empty_x, int empty_y, int x1, int y1, int x2, int y2, int x3, int y3, int x4, int y4); // this function is for blocks with four blocks around it. (for middle sections)
void shuffle_move(int board[][9], int size);

