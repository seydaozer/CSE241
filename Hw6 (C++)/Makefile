homework6: exe

exe: GTUVector.o GTUSet.o GTUIterator.o GTUIteratorConst.o main.o
	g++ GTUVector.o GTUSet.o GTUIterator.o GTUIteratorConst.o main.o -o exe

GTUVector.o: GTUVector.cpp
	g++ -c GTUVector.cpp

GTUSet.o: GTUSet.cpp
	g++ -c GTUSet.cpp

GTUIterator.o: GTUIterator.cpp
	g++ -c GTUIterator.cpp

GTUIteratorConst.o: GTUIteratorConst.cpp
	g++ -c GTUIteratorConst.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *o exe