all: word skipList main
	gcc word.o skipList.o main.o -o dicionario.out -std=c99 -Wall
	rm -f *.o

debug: word skipList main
	gcc word.o skipList.o main.o -o dicionario.out -std=c99 -Wall

word:
	gcc -c word.c -o word.o 

skipList:
	gcc -c skipList.c -o skipList.o
	 
main:
	gcc -c main.c -o main.o -std=c99
	 
clean:
	rm -f *.o *.out *.zip

run:
	./dicionario.out

zip:
	zip dicionario.zip *.c *.h Makefile
