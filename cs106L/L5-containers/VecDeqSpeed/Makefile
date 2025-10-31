CFLAGS = -O -std=c++17 -Wall
CC = clang++

all: VecDeqSpeed

VecDeqSpeed: VecDeqSpeed.o
	$(CC) $(CFLAGS) -o VecDeqSpeed VecDeqSpeed.o

clean:
	rm -f *.o VecDeqSpeed