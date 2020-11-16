board: exe

exe: abstractboard.o boardvector.o boardarray2d.o boardarray1d.o main.o
	g++ abstractboard.o boardvector.o boardarray2d.o boardarray1d.o main.o -o exe

abstractboard.o: abstractboard.cpp
	g++ -c abstractboard.cpp

boardvector.o: boardvector.cpp
	g++ -c boardvector.cpp

boardarray2d.o: boardarray2d.cpp
	g++ -c boardarray2d.cpp

boardarray1d.o: boardarray1d.cpp
	g++ -c boardarray1d.cpp

main.o: main.cpp
	g++ -c main.cpp

clean:
	rm -rf *o exe

