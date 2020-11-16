#include "abstractboard.h"
#include<iostream>

using namespace std;
namespace Boards{

	int AbstractBoard::number_of_boards = 0;

	AbstractBoard::AbstractBoard() : number_of_moves(0), last_move('S'), row(0), column(0), wall_number(0), empty_x(0), empty_y(0){
		number_of_boards++;
	}
	AbstractBoard::AbstractBoard(const AbstractBoard& other) : number_of_moves(other.number_of_moves), last_move(other.last_move),
								row(other.row), column(other.column), wall_number(other.wall_number), empty_x(other.empty_x), empty_y(other.empty_y)
	{
		number_of_boards++;
	}

	int AbstractBoard::NumberOfBoards() const{
		return number_of_boards;
	}

	int AbstractBoard::numberOfMoves() const{
		return number_of_moves;
	}
	char AbstractBoard::lastMove() const{
		return last_move;
	}
	void AbstractBoard::setNumberOfMoves(int moves){
		number_of_moves = moves;
	}
	void AbstractBoard::setLastMove(char move){
		last_move = move;
	}

	int AbstractBoard::getRow() const{
		return row;
	}

	int AbstractBoard::getColumn() const{
		return column;
	}

	int AbstractBoard::getCoordx() const{
		return empty_x;
	}

	int AbstractBoard::getCoordy() const{
		return empty_y;
	}

	bool validMoves(const vector<AbstractBoard*> boards){
		int row, column, empty_x, empty_y/*the empty cell's coordinates */,
		prev_x, prev_y/*I used these variables to the previous empty cell's coordinates for the loop*/;

		row = boards[0]->getRow();
		column = boards[0]->getColumn();
		empty_x = boards[0]->getCoordx();
		empty_y = boards[0]->getCoordy();

		bool flag; // I used this flag to call the isSolved because I can not use b outside the for(I have defined b in for).
		int count = 0; // I used this variable not to check the first round of the loop.
		for(AbstractBoard *b : boards){
			if(row != b->getRow() && column != b->getColumn())	return false;
			else{
				prev_x = empty_x;
				prev_y = empty_y;
				empty_x = b->getCoordx();
				empty_y = b->getCoordy();
				
				if( (prev_x - empty_x) == 1 && (prev_y - empty_y) == 0){ count++; } //LEFT
				else if ( (prev_x - empty_x) == -1 && (prev_y - empty_y) == 0){ count++; } //RIGHT
				else if ( (prev_y - empty_y) == 1 && (prev_x - empty_x) == 0){ count++; } //UP
				else if ( (prev_y - empty_y) == -1 && (prev_x - empty_x) == 0){ count++; } //DOWN
				else if(count == 0){ } // if the loop returns for the first time, the function should not return false.
				else	return false;
			}
			flag = b->isSolved();
		}
		return flag;
	}
}