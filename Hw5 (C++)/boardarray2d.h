#ifndef BOARDARRAY2D_H
#define BOARDARRAY2D_H

#include <string>
#include "abstractboard.h"
using namespace std;

namespace Boards{
	class BoardArray2D : public AbstractBoard {
	public:
		public:
		BoardArray2D();
		BoardArray2D(const BoardArray2D& other);
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
		void operator=(const BoardArray2D& other);
		void setFinalBoard();
		void initRandomBoard();
		void calculateWallNumber();
		bool movement(int x, int y);
		void findEmptyCell();
		~BoardArray2D();
	private:
		string **board;
		string *finalBoard;
	};
	
}

#endif //BOARDARRAY2D_H