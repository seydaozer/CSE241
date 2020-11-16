package HW7_171044023;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.IOException;

/**
 * @author Seyda Ozer
 *
 */
public class BoardArray1D extends AbstractBoard{
	
	/**
	 * This array of string is the 1D game board.
	 */
	private String [] board;
	
	/**
	 * This int value is the coordinate of empty cell in the 1d board.
	 */
	private int  empty_cell;
	
	/**
	 * BoardArray1D no-argument constructor
	 */
	public BoardArray1D() {
		super();
	}
	
	/**
	 * BoardArray1D two-arguments constructor
	 * @param newRow int value of row number
	 * @param newColumn int value of column number
	 */
	public BoardArray1D(int newRow, int newColumn) {
		super(newRow, newColumn);	
		board = new String[row*column];
	}
	
	/**
	 * This method returns string representation of BoardArray1D object.
	 *@return string of representation of BoardArray1D object
	 */
	@Override
	public String toString() {
		String res = board[0];
		
		for(int i=0; i<getRow()*getColumn(); i++) {
		
			if(i == 0)	res += " "; 
			else{
				res += board[i];
				res += " ";
			}
			if(i % getColumn() == getColumn()-1)
				res += "\n";
		}
		
		return res;
	}

	/**
	 * This method reads the board from the file given as parameter.
	 * @param file_name string of the file name
	 */
	@Override
	public void readFromFile(String file_name) {
		findSize(file_name);
		
		try {
		    FileReader read = new FileReader(file_name);
	        BufferedReader buffer = new BufferedReader(read);

	        String line;
	       
	        int empty = 0, begin = 0;
	        int i = 0;
	        
	        while ((line = buffer.readLine()) != null) {
	        	for(int j=0; j<getColumn(); j++) {
		        	// find first empty
		        	if(j == 0)	empty = line.indexOf(" ");
		        	
		        	//board == line
		        	if(empty == -1)	board[i] = line.substring(begin, line.length());
		        	else	board[i] = line.substring(begin, empty);

		        	begin = empty+1;
			        //find next empty
		        	empty = line.indexOf(" ", empty+1);
		        	
		        	i++;
	        	}
            }
			buffer.close();
			findEmptyCell();
			calculateWallNumber();
			fillCheckBoard();
		}
		catch (IOException e) {
            System.err.format("IOException: %s%n", e);
        }
	}

	/**
	 * This method writes the board to the file given as parameter.
	 * @param file_name string of the file name
	 */
	@Override
	public void writeToFile(String file_name) {
		try {
			FileWriter write = new FileWriter(file_name);
			BufferedWriter buffer = new BufferedWriter(write);
			
			for(int i=0; i<getRow()*getColumn(); i++) {
				buffer.write(board[i]);
				
				if(i % getColumn() != getColumn()-1 )
					buffer.write(" ");
				
				else if(i % getColumn() == getColumn()-1 )
					buffer.newLine();
			}

			buffer.close();
		}
		catch (IOException e) {
            System.err.format("IOException: %s%n", e);
        }
		
	}

	/**
	 *This method resets the board to the solution.
	 */
	@Override
	public void reset() {	
		int k = 0;
		
		for(int i=0; i<getRow() * getColumn(); i++){ // I filled the board with the numbers in the array(numbers).
				if(board[i].compareTo("00") != 0){
					board[i] = checkBoard[k];
					k++;
				}
		}
		setNumberOfMoves(0);
		
	}

	/**
	 * This method sets the board size to given values.
	 * The values are given as parameters and there are no restrictions on the board size.
	 * The board is reset after this operation.
	 * @param size1 int value of board's first size
	 * @param size2 int value of board's second size
	 */
	@Override
	public void setSize(int size1, int size2) {
		setRow(size1);
		setColumn(size2);
		calculateWallNumber();
		fillCheckBoard();
		reset();
		
	}

	/**
	 * This method makes a move according to the given char parameter.
	 * @param choice int value of user's choice for the move
	 */
	@Override
	public void move(char choice) {
		boolean flag = false;
		
		findEmptyCell();
		switch(choice){
			case 'L':	case 'l':	//LEFT
				if(getEmptyY() > 0)
					flag = movement(empty_cell-1);
				else	System.out.println("LEFT is invalid move!");
			break;

			case 'R':	case 'r':	//RIGHT
				if(getEmptyY() < getColumn()-1)
					flag = movement(empty_cell+1);
				else	System.out.println("RIGHT is invalid move!");
			break;

			case 'U':	case 'u':	//UP
				if(getEmptyX() > 0)
					flag = movement(empty_cell - getColumn());
				else	System.out.println("UP is invalid move!");
			break;

			case 'D':	case 'd':	//DOWN
				if(getEmptyX() < getRow()-1)
					flag = movement(empty_cell + getColumn());
				else	System.out.println("DOWN is invalid move!");
			break;
		}
		if(flag == true){
			findEmptyCell();
			setNumberOfMoves( numberOfMoves() + 1 );
			setLastMove(choice);
		}
		
	}

	/**
	 * This method checks if the board is solved..
	 * @return returns true if the board is a solution
	 */
	@Override
	public boolean isSolved() {
		int k = 0;
		System.out.println();
		for(int i=0; i<getRow() * getColumn(); i++){
				if(board[i].compareTo("00") != 0){
					if( board[i].compareTo(checkBoard[k]) != 0)	return false;
					k++;
				}
			
		}
		return true;
	}

	/**
	 * This method takes two indexes and returns the corresponding cell content.
	 * @param x int value of first index
	 * @param y int value of second index
	 * @return returns the value in the given coordinates.
	 */
	@Override
	public String cell(int x, int y) {
		int index = x * getColumn() + y;
		return board[index];
	}

	/**
	 * This method controls equality.
	 * Two boards are equal, if the boards are the same.
	 * This method does not consider last move or the number of steps.
	 * @param other the object of AbstractBoard
	 * @return returns true if two boards are equal.
	 */
	@Override
	public boolean Equals(AbstractBoard other) {
		
		if(getRow() == other.getRow() && getColumn() ==  other.getColumn()) {
			for(int i=0; i<getRow(); i++) {
				for(int j=0; j<getColumn(); j++) {
					if( this.cell(i, j).compareTo( other.cell(i, j) ) != 0)	return false;
				}
			}
		}
		else	return false;
		
		return true;
	}
	
	/**
	 * This method swaps the empty cell and the cell in the index given as parameter.
	 * @param index int value of the index of the cell to move
	 * @return returning true, if the cell can move.
	 */
	private boolean movement(int index){
		String temp;

		findEmptyCell();
		if(board[index].compareTo("00") != 0){
			temp = board[empty_cell];
			board[empty_cell] = board[index];
			board[index] = temp;
			return true;
		}
		else	System.out.println("Empty cell cannot move!");
		return false;
	}
	
	/**
	 * This method calculates the number of wall in the board.
	 */
	private void calculateWallNumber() {
		int count = 0;
		
		for(int i=0; i<getRow() * getColumn(); i++) {
				if(board[i].compareTo("00") == 0) count++;
		}
		
		setWallNumber(count);
	}
	
	/**
	 * This method finds the empty cell's current coordinates.
	 */
	private void findEmptyCell() {
		int x = 0, y = 0;
			
		for(int i=0; i<getRow()*getColumn(); i++) {
			if(board[i].compareTo("bb") == 0) {
				x = i/column;
				y = i%column;
				empty_cell = i;
			}
		}	
		setEmptyCell(x, y);
	}
	
	/**
	 * This method finds the sizes of the board read from the file.
	 * @param file_name the string of the name of the file to be read
	 */
	private void findSize(String file_name) {
		try {
		    FileReader read = new FileReader(file_name);
	        BufferedReader buffer = new BufferedReader(read);
	        
	        int size1 = 0;
	        int size2 = 1;
	        
	        String line;
	        
	        while ((line = buffer.readLine()) != null) {
	        	if(size1 == 0){
	        		int i = 0;
		        	while(i < line.length() ) {
		        		if(line.charAt(i) == ' ') size2++;
		        		i++;
		        	}
	        	}
	        	size1++;
            }
			buffer.close();
			
			setRow(size1);
			setColumn(size2);
			
			board = new String[getRow() * getColumn()];	
		}
		catch (IOException e) {
            System.err.format("IOException: %s%n", e);
        }
	}
}
