CC=g++
CPPFLAGS=-g -Wall -ggdb -ansi -O0
LIBS=
OBJECTS=Sudoku.o Square.o tools.o Board.o Cluster.o Tests.o SquareState.o Game.o BadMove.o IllegalInput.o ConflictingValue.o FatalException.o

all: Sudoku libsudoku.a

libsudoku.a: Square.o tools.o Board.o Cluster.o Tests.o SquareState.o
	ar cr libsudoku.a Square.o tools.o Board.o Cluster.o Tests.o SquareState.o

Sudoku: $(OBJECTS)
	$(CC) -o Sudoku $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

clean: 
	rm -rf *.o
	rm -rf Sudoku
	rm -rf *.a
