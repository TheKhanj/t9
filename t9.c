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

void search(trie_t *trie);

void inject_file_into_trie(trie_t *trie, char *filename);

int main(int argc, char **argv) {

	trie_t trie;
	trie_init(&trie);
	inject_file_into_trie(&trie, argv[1]);
	search(&trie);
	trie_deinit(&trie);
	return 0;
}

void inject_file_into_trie(trie_t *trie, char *filename) {
	FILE *dict = fopen(filename, "r");
	if (dict == NULL) {
		fprintf(stderr, "File does not exist\n");
		// TODO: add error
		return;
	}

	char word[MAX_LINE];
	while (fgets(word, MAX_LINE, dict) != NULL) {
		trie_add_word(trie, word);
	}

	fclose(dict);
}

void search(trie_t *trie) {
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
			trie_get_word(trie, input, ret);
			pos++;
		}
		refresh();
	}
}
