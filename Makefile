t9: t9.o node.o trie.o llist.o error.o
	gcc -Wall -std=c99 -g -o t9 t9.o node.o trie.o llist.o error.o -lncurses

t9.o: node.h t9.c
	gcc -Wall -std=c99 -g -c t9.c

node.o: node.h node.c
	gcc -Wall -std=c99 -g -c node.c

trie.o: trie.h trie.c
	gcc -Wall -std=c99 -g -c trie.c

llist.o: llist.h llist.c
	gcc -Wall -std=c99 -g -c llist.c

error.o: error.h error.c
	gcc -Wall -std=c99 -g -c error.c
