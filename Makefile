CC=g++
CPPFLAGS=-g -Wall -ggdb -ansi 
LIBS=
OBJECTS=Sudoku.o Square.o tools.o Board.o Cluster.o Tests.o

all: Sudoku

Sudoku: $(OBJECTS)
	$(CC) -o Sudoku $(OBJECTS)

$(OBJECTS): %.o: %.cpp
	$(CC) -c $(CPPFLAGS) $< -o $@

clean: 
	rm -rf *.o
	rm -rf Sudoku
