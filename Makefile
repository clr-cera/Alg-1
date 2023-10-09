all: word skipList main
	gcc word.o skipList.o main.o -o dicionario.out -std=c99 -Wall

debug: word skipList main
	gcc -g word.o skipList.o main.o -o dicionario.out -std=c99 -Wall

word:
	gcc -c -g word.c -o word.o 

skipList:
	gcc -c -g skipList.c -o skipList.o
	 
main:
	gcc -c -g main.c -o main.o -std=c99
	 
clean:
	rm -f *.o *.out *.zip

run:
	./dicionario.out

zip:
	zip dicionario.zip *.c *.h Makefile
