#ifndef ABSTRACTBOARD_H
#define ABSTRACTBOARD_H

#include <string>
#include<vector>
using std::string;
using std::vector;

namespace Boards{
	class AbstractBoard{
	public:
		AbstractBoard();
		AbstractBoard(const AbstractBoard& other);
		virtual void setSize(int, int) = 0;
		virtual void print() const = 0;
		virtual void readFromFile(string file_name) = 0;
		virtual void writeToFile() const = 0;
		virtual void reset() = 0;
		virtual void move(char choice) = 0;
		virtual bool isSolved() = 0;
		virtual string operator()(const int x, const int y) const = 0;
		virtual bool operator==(AbstractBoard& other) = 0;
		int NumberOfBoards() const;
		char lastMove() const;
		int numberOfMoves() const;
		void setNumberOfMoves(int moves);
		void setLastMove(char move);
		int getRow() const;
		int getColumn() const;
		int getCoordx() const;
		int getCoordy() const;
	protected:
		int row, column;
		int empty_x, empty_y;
		int wall_number;
		char last_move;
		int number_of_moves;
		static int number_of_boards;
	};

	bool validMoves(const vector<AbstractBoard*> boards);
}

#endif //ABSTRACTBOARD_H