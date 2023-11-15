all: queue item tree sets main
	gcc *.o -o sets.out -std=c99 -Wall
	rm -f *.o

main:
	gcc -c main.c -o main.o -std=c99
	 
tree:
	gcc -c ./BTAVL/avlBinaryTree.c -o tree.o -std=c99

item:
	gcc -c ./Item/item.c -o item.o -std=c99

queue:
	gcc -c ./Queue/queue.c -o queue.o -std=c99

sets:
	gcc -c ./Sets/set.c -o sets.o -std=c99

clean:
	rm -f *.o *.out *.zip

run:
	./sets.out

zip:
	zip sets.zip *.c *.h Makefile
