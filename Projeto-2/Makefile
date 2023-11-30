all: queue item tree sets main
	gcc *.o -g -o sets.out -std=c99 -Wall
	rm -f *.o

main:
	gcc -c -g ./src/main.c -o main.o -std=c99
	 
tree:
	gcc -c -g ./src/BTAVL/avlBinaryTree.c -o tree.o -std=c99

item:
	gcc -c -g ./src/Item/item.c -o item.o -std=c99

queue:
	gcc -c -g ./src/Queue/queue.c -o queue.o -std=c99

sets:
	gcc -c -g ./src/Sets/set.c -o sets.o -std=c99

clean:
	rm -f *.o *.out *.zip

run:
	./sets.out

zip:
	zip -R sets.zip . '*.c' '*.h' '*.in' 'Makefile'

zip-all:
	zip -R sets.zip . '*'