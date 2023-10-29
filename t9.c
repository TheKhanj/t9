#include <assert.h>
#include <ctype.h>
#include <curses.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "trie.h"

#define MAX_LINE 100

void search(node_t *root);

int main(int argc, char **argv) {
	FILE *dict = fopen(argv[1], "r");
	char word[MAX_LINE];
	node_t *root = node_new();
	node_t *temp;
	if (dict == NULL) {
		fprintf(stderr, "File does not exist\n");
		return 1;
	}
	while (fgets(word, MAX_LINE, dict) != NULL) {
		temp = root;
		trie_add_word(temp, word);
	}
	fclose(dict);
	search(root);
	node_free_all(root);
	return 0;
}

void search(node_t *root) {
	cbreak();
	echo();
	initscr();
	char input[MAX_LINE], ret[MAX_LINE];
	int pos = 0;

	while (true) {
		char x = getch();
		input[pos] = x;
		input[pos + 1] = 0;

		if (x == EOF) {
			pos = 0;
		} else {
			trie_get_word(input, root, ret);
			pos++;
		}
		refresh();
	}
}
