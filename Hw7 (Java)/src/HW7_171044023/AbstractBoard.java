package HW7_171044023;

/**
 * @author Seyda Ozer
 *
 */
public abstract class AbstractBoard {
	
	/**
	 *This int value is number of rows in the board.
	 */
	protected int row;
	
	/**
	 * This int value is number of columns in the board.
	 */
	protected int column;
	
	/**
	 * This char value is the last move made on the board.
	 */
	protected char last_move;
	
	/**
	 * This int value is the number of moves made on the board.
	 */
	protected int number_of_moves;
	
	/**
	 * This static int value is number of boards(objects).
	 */
	protected static int number_of_boards = 0;
	
	/**
	 * This int value is number of wall in the board.
	 */
	protected int wall_number;
	
	/**
	 * This int value is the x coordinate of the empty cell in the board.
	 */
	protected int empty_x;
	
	/**
	 * This int value is the y coordinate of the empty cell in the board.
	 */
	protected int empty_y;
	
	/**
	 * This array of string is the final board.
	 */
	protected String [] checkBoard;

	/**
	 * AbstractBoard no-argument constructor: initialize for
	 * each fields to zero except for last move that its initial condition is 'S'.
	 * Add 1 to the number_of_boards.
	 */
	public AbstractBoard() {
		this(0, 0);
	}
	
	/**
	 * AbstractBoard two-argument constructor: Add 1 to the number_of_boards.
	 * @param newRow int value of row number
	 * @param newColumn int value of column number
	 */
	public AbstractBoard(int newRow, int newColumn) {
		row = newRow;
		column = newColumn;
		last_move = 'S';
		number_of_moves = 0;
		wall_number = 0;
		checkBoard = new String[row*column];
		
		number_of_boards++;
	}
	
	/**
	 * This method returns string representation of AbstractBoard object.
	 *@return string of representation of AbstractBoard object
	 */
	public abstract String toString();
	
	/**
	 * This method reads the board from the file given as parameter.
	 * @param file_name string of the file name
	 */
	public abstract void readFromFile(String file_name);
	
	/**
	 * This method writes the board to the file given as parameter.
	 * @param file_name string of the file name
	 */
	public abstract void writeToFile(String file_name);

	/**
	 * This method resets the board to the solution.
	 */
	public abstract void reset();
	
	/**
	 * This method sets the board size to given values.
	 * The values are given as parameters and there are no restrictions on the board size.
	 * The board is reset after this operation.
	 * @param size1 int value of board's first size
	 * @param size2 int value of board's second size
	 */
	public abstract void setSize(int size1, int size2);
	
	/**
	 * This method makes a move according to the given char parameter.
	 * @param choice int value of user's choice for the move
	 */
	public abstract void move(char choice);
	
	/**
	 * This method checks if the board is solved..
	 * @return returns true if the board is a solution
	 */
	public abstract boolean isSolved();
	
	/**
	 * This method takes two indexes and returns the corresponding cell content.
	 * @param x int value of first index
	 * @param y int value of second index
	 * @return returns the value in the given coordinates.
	 */
	public abstract String cell(int x, int y);
	
	/**
	 * This method controls equality.
	 * Two boards are equal, if the boards are the same.
	 * This method does not consider last move or the number of steps.
	 * @param other the object of AbstractBoard
	 * @return returns true if two boards are equal.
	 */
	public abstract boolean Equals(AbstractBoard other);

	/**
	 * This static method to get static number of boards variable.
	 * @return int value of number of boards
	 */
	public static int NumberOfBoards() {
		return number_of_boards;
	}
	
	/**
	 * This method sets last move.
	 * @param move char value of last move
	 */
	public void setLastMove(char move) {
		last_move = move;
	}
	
	/**
	 * This method gets last move.
	 * @return char value of last move
	 */
	public char lastMove() {
		if(number_of_moves == 0)
			last_move = 'S';
		return last_move;
	}
	
	/**
	 * This method sets number of moves.
	 * @param moves int value of number of moves
	 */
	public void setNumberOfMoves(int moves) {
		number_of_moves = moves;
	}
	
	/**
	 * This method gets number of moves.
	 * @return int value of number of moves
	 */
	public int numberOfMoves() {
		return number_of_moves;
	}
	
	
	/**
	 * This method sets row number.
	 * @param newRow int value of row number
	 */
	public void setRow(int newRow) {
		row = newRow;
	}
	
	/**
	 * This method gets row number.
	 * @return int value of row number
	 */
	public int getRow() {
		return row;
	}
	
	/**
	 * This method sets column number.
	 * @param newColumn int value of column number
	 */
	public void setColumn(int newColumn) {
		column = newColumn;
	}
	
	/**
	 * This method gets column number
	 * @return int value of column number
	 */
	public int getColumn() {
		return column;
	}
	
	
	/**
	 * This method sets wall number in the board
	 * @param new_wall_num int value of wall number
	 */
	public void setWallNumber(int new_wall_num) {
		wall_number = new_wall_num;
	}

	
	/**
	 * This method gets wall number in the board
	 * @return int value of wall number
	 */
	public int getWallNumber() {
		return wall_number;
	}
	
	/**
	 * This method sets the coordinates of the Empty cell.
	 * @param newX int value of empty cell's x coordinates.
	 * @param newY int value of empty cell's y coordinates.
	 */
	public void setEmptyCell(int newX, int newY) {
		empty_x = newX;
		empty_y = newY;
	}
	
	/**
	 * This method gets the x coordinate of the Empty cell.
	 * @return int value of x coordinate of empty cell
	 */
	public int getEmptyX() {
		return empty_x;
	}
	
	/**
	 * This method gets the y coordinate of the Empty cell.
	 * @return int value of y coordinate of empty cell
	 */
	public int getEmptyY() {
		return empty_y;
	}
	
	/**
	 * This method fills the check board.
	 */
	public void fillCheckBoard(){ 
		checkBoard = new String[row*column];
		
		if(getRow() * getColumn() - getWallNumber() > 0){
			int [] temp = new int[getRow() * getColumn()];
			
			for(int i=0; i<getRow() * getColumn() - getWallNumber() - 1; i++)
				temp[i] = i+1;
			
			
			for(int i=0; i<getRow() * getColumn() - getWallNumber() - 1; i++){
				if(temp[i] > 9){
					checkBoard[i] = Integer.toString(temp[i]);
				}
				else{
					checkBoard[i] = "0";
					checkBoard[i] += Integer.toString(temp[i]);
				}
			}

			checkBoard[getRow() * getColumn() - getWallNumber() - 1] = "bb"; 
		}
	}

}
