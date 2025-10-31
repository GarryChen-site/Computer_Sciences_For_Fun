CFLAGS = -O -std=c++17 -Wall
CC = clang++

all: DequeSpeed

DequeSpeed: DequeSpeed.o
	$(CC) $(CFLAGS) -o DequeSpeed DequeSpeed.o

clean:
	rm -f *.o DequeSpeed