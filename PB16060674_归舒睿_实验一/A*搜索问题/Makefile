CC=g++

all: bin/Astar bin/IDAstar

bin/Astar: src/Astar.cpp src/Astar.h
	$(CC) -o bin/Astar src/Astar.cpp
bin/IDAstar: src/IDAstar.cpp src/IDAstar.h
	$(CC) -o bin/IDAstar src/IDAstar.cpp

clean:
	rm bin/*