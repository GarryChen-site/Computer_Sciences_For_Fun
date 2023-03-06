

transistors:	transistors.o io.o
	gcc -o transistors transistors.o io.o

transistors.o:	transistors.c transistors.h
	gcc -c transistors.c

io.o:	io.c
	gcc -c io.c

clean:
	rm -f *.o transistors