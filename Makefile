CC = g++
CFLAGS = -I -g -w -Wall -std=c++14

all: main test

main: src/main.cpp src/types/types.hpp  src/board/pieces.cpp src/board/board.cpp src/client/client.cpp src/ai/minmax.cpp
	$(CC) $(CFLAGS) -o ./bin/othello src/main.cpp src/types/types.hpp src/board/pieces.cpp src/board/board.cpp src/client/client.cpp src/ai/minmax.cpp

test: src/types/types.hpp src/board/pieces.cpp src/board/board.cpp src/client/client.cpp ./test/suite1.cpp ./test/suite2.cpp src/ai/minmax.cpp
	$(CC) $(CFLAGS) -o ./test/bin/testSuite1 src/types/types.hpp src/board/pieces.cpp src/board/board.cpp src/client/client.cpp src/ai/minmax.cpp ./test/suite1.cpp
	$(CC) $(CFLAGS) -o ./test/bin/testSuite2 src/types/types.hpp src/board/pieces.cpp src/board/board.cpp src/client/client.cpp src/ai/minmax.cpp ./test/suite2.cpp

clean:
	rm ./bin/*; rm ./test/bin/*