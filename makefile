# this file allows for the compilation of both .c files for practicum 1

all: prac1

prac1: prac1.o compress.o
	gcc prac1.o compress.o -o prac1

prac1.o: prac1.c
	gcc -c prac1.c

compress.o: compress.c
	gcc -c compress.c

clean:
	rm *o prac1
