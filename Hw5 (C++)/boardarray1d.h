#ifndef BOARDARRAY1D_H
#define BOARDARRAY1D_H

#include "abstractboard.h"

namespace Boards{
	class BoardArray1D : public AbstractBoard {
	public:
		BoardArray1D();
		BoardArray1D(const BoardArray1D& other);
		//abstractboard
		void setSize(int size1, int size2) override;
		void print() const override;
		void readFromFile(string file_name) override;
		void writeToFile() const override;
		void reset() override;
		void move(char choice) override;
		bool isSolved() override;
		string operator()(const int x,const int y) const override;
		bool operator==(AbstractBoard& other);
		//end
		void operator=(const BoardArray1D& other);
		void setFinalBoard();
		void initRandomBoard();
		void calculateWallNumber();
		bool movement(int i);
		void findEmptyCell();
		~BoardArray1D();
	private:
		string *board;
		string *finalBoard;
		int empty;	
	};
}
#endif //BOARDARRAY1D_H