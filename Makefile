all: minesweeper

SOURCES:=minesweeper.cpp minefield.cpp

clean:
	-rm -rf minesweeper
	-rm -rf *.o

minesweeper: $(SOURCES)
	g++ $^ -o $@

test: minesweeper
	./minesweeper test_data.txt >output.txt
	diff correct_test_output.txt output.txt
	echo Test succeeded.
