package HW7_171044023;

import java.util.Scanner;

/**
 * @author Seyda Ozer
 *
 */
public class Test {
	
	/**
	 * This static method that takes an array of AbstractBoard references and
	 * checks whether the array contains a valid sequence of moves for a solution.
	 * @param boards array of AbstractBoard.
	 * @return returns true if the array contains a valid sequence of moves for a solution.
	 */
	public static boolean validMoves(AbstractBoard [] boards) {
		int i;
		int length = boards.length;
		
		for(i=0; i<length-1; i++) {
			if(  ( boards[i].getRow() != boards[i+1].getRow() ) || 
				( boards[i].getColumn() != boards[i+1].getColumn() )  )
				return false;
			else {
				if( ( boards[i].getEmptyX() - boards[i+1].getEmptyX() ) == 1 
					&& ( boards[i].getEmptyY() - boards[i+1].getEmptyY() ) == 0){ /*LEFT*/ }
				else if ( ( boards[i].getEmptyX() - boards[i+1].getEmptyX() ) == -1
						&& ( boards[i].getEmptyY() - boards[i+1].getEmptyY() ) == 0){ /*RIGHT*/ } 
				else if ( ( boards[i].getEmptyY() - boards[i+1].getEmptyY() ) == 1
					&& ( boards[i].getEmptyX() - boards[i+1].getEmptyX() ) == 0){ /*UP*/ } 
				else if ( ( boards[i].getEmptyY() - boards[i+1].getEmptyY() ) == -1
						&& ( boards[i].getEmptyX() - boards[i+1].getEmptyX() ) == 0){ /*DOWN*/ }
				else	return false;
			}
		}
		return boards[i].isSolved();
	}
	
	/**
	 * This main method of this application.
	 * @param args array of string arguments.
	 */
	public static void main(String[] args) {
		String file_name = "seyda.txt";
		int choice;
		System.out.println("Please, enter the board type");
		System.out.println("1- BoardArray1D(The Board is represented using a two dimensional dynamic C array.)");
		System.out.println("2- BoardArray2D(The Board is represented using a one dimensional dynamic C array.)");
		
		try (Scanner input = new Scanner(System.in)) {
			choice = input.nextInt();
		}
		System.out.println();
		
		if(choice == 1){ //BoardArray1D
			AbstractBoard b1 = new BoardArray1D();
			AbstractBoard b2 = new BoardArray1D();
			AbstractBoard b3 = new BoardArray1D();
			
			System.out.println("---------------------------------------------------------------------");
			b1.readFromFile(file_name);
			System.out.println("The first board game is read from the file(" + file_name + ").");
			System.out.print("The first board:\n" + b1);
			System.out.println("---------------------------------------------------------------------");
			b2.readFromFile(file_name);
			System.out.println("The second board game is read from the file(" + file_name + ").");
			b2.move('L');
			System.out.print("The second board:\n" + b2);
			
			System.out.println("---------------------------------------------------------------------");
			if(b1.Equals(b2))	System.out.println("First board and second board are equal.");
			else	System.out.println("First board and second board are not equal.");
			
			System.out.println("---------------------------------------------------------------------");
			b3.readFromFile(file_name);
			System.out.println("The third board game is read from the file(" + file_name + ").");
			b3.move('L');
			b3.move('L');
			System.out.print("The third board:\n" + b3);
			System.out.println("---------------------------------------------------------------------");
			
			//Test validMoves
			AbstractBoard [] boards = new AbstractBoard[3];
			boards[0] = b1;
			boards[1] = b2;
			boards[2] = b3;
			
			if(validMoves(boards) == true)	System.out.println("This array contains a valid sequence of moves for a solution.");
			else	System.out.println("This array does not contain a valid sequence of moves for a solution.");
			System.out.println("---------------------------------------------------------------------");
			
			//testing isSolved()
			System.out.print("The third board:\n" + b3);
			if(b3.isSolved() == true)	System.out.println("This board is solved.\n");
			else	System.out.println("This board is not solved.\n");
			
			b3.reset();
			System.out.print("The third board is reset.\n" + b3);
			
			if(b3.isSolved() == true)	System.out.println("This board is solved.");
			else	System.out.println("This board is not solved.");
			System.out.println("---------------------------------------------------------------------");
			
			System.out.println("After resetting the third board:");
			if(validMoves(boards) == true)	System.out.println("This array contains a valid sequence of moves for a solution.");
			else	System.out.println("This array does not contain a valid sequence of moves for a solution.");
			System.out.println("---------------------------------------------------------------------");
			
			b3.move('L');
			System.out.println("The last move is: " + b3.lastMove() + " , and the number of moves: " + b3.numberOfMoves() + "\n" + b3);
			b3.move('U');
			System.out.println("The last move is: " + b3.lastMove() + " , and the number of moves: " + b3.numberOfMoves() + "\n" + b3);
			b3.move('R');
			System.out.println("The last move is: " + b3.lastMove() + " , and the number of moves: " + b3.numberOfMoves() + "\n" + b3);
			b3.move('D');
			System.out.println("The last move is: " + b3.lastMove() + " , and the number of moves: " + b3.numberOfMoves() + "\n" + b3);
			System.out.println("---------------------------------------------------------------------");
			
			b3.writeToFile("SeydaOzer.txt");
			System.out.println("This board was written to the file named SeydaOzer.txt");
			b3.setSize(3,  4);
			System.out.println("This card is set to size 3, 4 and reset.\n" + b3);
			System.out.println("The value of the board[1][2] is: " + b3.cell(1, 2));
			System.out.println("---------------------------------------------------------------------");
		
			System.out.println("The board number which has been created so far: " + BoardArray1D.NumberOfBoards() );
			System.out.println("---------------------------------------------------------------------");
		}
		
		if(choice == 2){ //BoardArray2D
			AbstractBoard b1 = new BoardArray2D();
			AbstractBoard b2 = new BoardArray2D();
			AbstractBoard b3 = new BoardArray2D();
			
			System.out.println("---------------------------------------------------------------------");
			b1.readFromFile(file_name);
			System.out.println("The first board game is read from the file(" + file_name + ").");
			System.out.print("The first board:\n" + b1);
			System.out.println("---------------------------------------------------------------------");
			b2.readFromFile(file_name);
			System.out.println("The second board game is read from the file(" + file_name + ").");
			b2.move('L');
			System.out.print("The second board:\n" + b2);
			
			System.out.println("---------------------------------------------------------------------");
			if(b1.Equals(b2))	System.out.println("First board and second board are equal.");
			else	System.out.println("First board and second board are not equal.");
			
			System.out.println("---------------------------------------------------------------------");
			b3.readFromFile(file_name);
			System.out.println("The third board game is read from the file(" + file_name + ").");
			b3.move('L');
			b3.move('L');
			System.out.print("The third board:\n" + b3);
			System.out.println("---------------------------------------------------------------------");
			
			//Test validMoves
			AbstractBoard [] boards = new AbstractBoard[3];
			boards[0] = b1;
			boards[1] = b2;
			boards[2] = b3;
			
			if(validMoves(boards) == true)	System.out.println("This array contains a valid sequence of moves for a solution.");
			else	System.out.println("This array does not contain a valid sequence of moves for a solution.");
			System.out.println("---------------------------------------------------------------------");
			
			//testing isSolved()
			System.out.print("The third board:\n" + b3);
			if(b3.isSolved() == true)	System.out.println("This board is solved.\n");
			else	System.out.println("This board is not solved.\n");
			
			b3.reset();
			System.out.print("The third board is reset.\n" + b3);
			
			if(b3.isSolved() == true)	System.out.println("This board is solved.");
			else	System.out.println("This board is not solved.");
			System.out.println("---------------------------------------------------------------------");
			
			System.out.println("After resetting the third board:");
					if(validMoves(boards) == true)	System.out.println("This array contains a valid sequence of moves for a solution.");
					else	System.out.println("This array does not contain a valid sequence of moves for a solution.");
			System.out.println("---------------------------------------------------------------------");
					
			b3.move('L');
			System.out.println("The last move is: " + b3.lastMove() + " , and the number of moves: " + b3.numberOfMoves() + "\n" + b3);
			b3.move('U');
			System.out.println("The last move is: " + b3.lastMove() + " , and the number of moves: " + b3.numberOfMoves() + "\n" + b3);
			b3.move('R');
			System.out.println("The last move is: " + b3.lastMove() + " , and the number of moves: " + b3.numberOfMoves() + "\n" + b3);
			b3.move('D');
			System.out.println("The last move is: " + b3.lastMove() + " , and the number of moves: " + b3.numberOfMoves() + "\n" + b3);
			System.out.println("---------------------------------------------------------------------");
			
			b3.writeToFile("SeydaOzer.txt");
			System.out.println("This board was written to the file named SeydaOzer.txt");
			b3.setSize(3,  4);
			System.out.println("This card is set to size 3, 4 and reset.\n" + b3);
			System.out.println("The value of the board[1][2] is: " + b3.cell(1, 2));
			System.out.println("---------------------------------------------------------------------");
		
			System.out.println("The board number which has been created so far: " + BoardArray1D.NumberOfBoards() );
			System.out.println("---------------------------------------------------------------------");
		}
		
		//Extra Test for validMoves ( 1D array and 2D array mixed here)
		System.out.println("\n");
		System.out.println("---------------------------------------------------------------------");
		System.out.println("Extra test for 1D and 2D game boards:");
		System.out.println("---------------------------------------------------------------------");
		AbstractBoard b1 = new BoardArray1D();
		AbstractBoard b2 = new BoardArray2D();
		AbstractBoard b3 = new BoardArray1D();
		
		System.out.println("---------------------------------------------------------------------");
		b1.readFromFile(file_name);
		System.out.println("The first board game is read from the file(" + file_name + ").");
		System.out.print("The first board:\n" + b1);
		System.out.println("---------------------------------------------------------------------");
		b2.readFromFile(file_name);
		System.out.println("The second board game is read from the file(" + file_name + ").");
		b2.move('L');
		System.out.print("The second board:\n" + b2);
		
		System.out.println("---------------------------------------------------------------------");
		if(b1.Equals(b2))	System.out.println("First board and second board are equal.");
		else	System.out.println("First board and second board are not equal.");
		
		System.out.println("---------------------------------------------------------------------");
		b3.readFromFile(file_name);
		System.out.println("The third board game is read from the file(" + file_name + ").");
		b3.move('L');
		b3.move('L');
		System.out.print("The third board:\n" + b3);
		System.out.println("---------------------------------------------------------------------");
		
		//Test validMoves
		AbstractBoard [] boards = new AbstractBoard[3];
		boards[0] = b1;
		boards[1] = b2;
		boards[2] = b3;
		
		if(validMoves(boards) == true)	System.out.println("This array contains a valid sequence of moves for a solution.");
		else	System.out.println("This array does not contain a valid sequence of moves for a solution.");
		System.out.println("---------------------------------------------------------------------");
		
	}

}
