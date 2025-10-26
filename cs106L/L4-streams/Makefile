CFLAGS = -O -std=c++17 -Wall
CC = clang++

all: input output

input: inputStreams.o
	$(CC) $(CFLAGS) -o input inputStreams.o

output: outputStreams.o
	$(CC) $(CFLAGS) -o output outputStreams.o

clean:
	rm -f *.o input output