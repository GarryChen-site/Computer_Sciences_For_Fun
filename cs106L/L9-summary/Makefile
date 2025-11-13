CFLAGS = -O -std=c++17 -Wall
CC = clang++
SRC = chal2.cpp 
OBJ = $(SRC:.cpp = .o) 

chal2: $(OBJ) 
	$(CC) $(CFLAGS) -o chal2 $(OBJ) 
clean:
	rm -f chal2 *.o