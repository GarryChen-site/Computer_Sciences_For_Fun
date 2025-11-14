CFLAGS = -O -std=c++17 -Wall
CC = clang++
SRC = chal6.cpp
OBJ = $(SRC:.cpp = .o) 

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

chal2: chal2.o
	$(CC) $(CFLAGS) -o chal2 chal2.o

chal6: chal6.o 
	$(CC) $(CFLAGS) -o chal6 chal6.o
clean:
	rm -f main chal2 chal6 *.o