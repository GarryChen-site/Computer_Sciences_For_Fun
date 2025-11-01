CFLAGS = -O -std=c++17 -Wall
CC = clang++

all: InsertionSpeed

InsertionSpeed: InsertionSpeed.o
	$(CC) $(CFLAGS) -o InsertionSpeed InsertionSpeed.o

clean:
	rm -f *.o InsertionSpeed