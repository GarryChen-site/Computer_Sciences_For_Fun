CFLAGS = -O -g -std=c++17 -Wall
CC = clang++
SRC = main.cpp
OBJ = $(SRC:.cpp=.o)

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

clean:
	rm -f main *.o