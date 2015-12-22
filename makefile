# Sudoku Solver Makefile

# compile
compile:
	g++ -Wall -g -c Sudoku.cpp
	g++ -Wall -g -c SudokuSolver.cpp
	g++ -o sudoku Sudoku.o SudokuSolver.o

# run
run:
	./sudoku

# clean compiled stuff
clean:
	rm -rf *.o
	rm -rf *.dSYM
	rm sudoku