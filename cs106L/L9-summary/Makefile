CFLAGS = -O -std=c++23 -Wall
CC = clang++
SRC = main.cpp
OBJ = $(SRC:.cpp = .o) 

main: $(OBJ)
	$(CC) $(CFLAGS) -o main $(OBJ)

chal2: chal2.o
	$(CC) $(CFLAGS) -o chal2 chal2.o

chal4: chal4.o 
	$(CC) $(CFLAGS) -o chal4 chal4.o

chal5: chal5.o 
	$(CC) $(CFLAGS) -o chal5 chal5.o

chal6: chal6.o 
	$(CC) $(CFLAGS) -o chal6 chal6.o
clean:
	rm -f main chal2 chal4 chal5 chal6 *.o