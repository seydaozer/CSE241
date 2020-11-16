171044023: exe

exe: main.o menu.o random_board.o control_elements.o print_board.o control_positions.o find_empty_cell.o movement.o intelligent_move.o find_distance.o find_current_number.o find_true_position.o two_locate_move.o three_locate_move.o four_locate_move.o shuffle_move.o
	g++ main.o menu.o random_board.o control_elements.o print_board.o control_positions.o find_empty_cell.o movement.o intelligent_move.o find_distance.o find_current_number.o find_true_position.o two_locate_move.o three_locate_move.o four_locate_move.o shuffle_move.o -o exe

main.o: main.cpp
	g++ -c main.cpp

menu.o: menu.cpp
	g++ -c menu.cpp

random_board.o: random_board.cpp
	g++ -c random_board.cpp

control_elements.o: control_elements.cpp
	g++ -c control_elements.cpp

print_board.o: print_board.cpp
	g++ -c print_board.cpp

control_positions.o: control_positions.cpp
	g++ -c control_positions.cpp

find_empty_cell.o: find_empty_cell.cpp
	g++ -c find_empty_cell.cpp

movement.o: movement.cpp
	g++ -c movement.cpp

intelligent_move.o: intelligent_move.cpp
	g++ -c intelligent_move.cpp

find_distance.o: find_distance.cpp
	g++ -c find_distance.cpp

find_current_number.o: find_current_number.cpp
	g++ -c find_current_number.cpp

find_true_position.o: find_true_position.cpp
	g++ -c find_true_position.cpp

two_locate_move.o: two_locate_move.cpp
	g++ -c two_locate_move.cpp

three_locate_move.o: three_locate_move.cpp
	g++ -c three_locate_move.cpp

four_locate_move.o: four_locate_move.cpp
	g++ -c four_locate_move.cpp

shuffle_move.o: shuffle_move.cpp
	g++ -c shuffle_move.cpp

clean:
	rm -rf *o exe

