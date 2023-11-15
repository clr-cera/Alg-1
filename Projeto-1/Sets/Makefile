all: main
	gcc main.o -o sets.out -std=c99 -Wall
	rm -f *.o

main:
	gcc -c main.c -o main.o -std=c99
	 
clean:
	rm -f *.o *.out *.zip

run:
	./sets.out

zip:
	zip sets.zip *.c *.h Makefile
