#ifndef BOARDVECTOR_H
#define BOARDVECTOR_H

#include <vector>
#include <string>
#include "abstractboard.h"
using namespace std;

namespace Boards{
	class BoardVector : public AbstractBoard {
	public:
		BoardVector();
		BoardVector(const BoardVector& other);
		//abstractboard
		void setSize(int size1, int size2) override;
		void print() const override;
		void readFromFile(string file_name) override;
		void writeToFile() const override;
		void reset() override;
		void move(char choice) override;
		bool isSolved() override;
		string operator()(const int x, const int y) const override;
		bool operator==(AbstractBoard& other);
		//end
		void operator=(const BoardVector& other);
		void setFinalBoard();
		void initRandomBoard();
		void calculateWallNumber();
		bool movement(int x, int y);
		void findEmptyCell();
		~BoardVector();
	private:
		vector < vector<string> > board;
		string *finalBoard;
	};	
}
#endif //BOARDVECTOR_H