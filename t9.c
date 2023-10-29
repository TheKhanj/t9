#include <assert.h>
#include <ctype.h>
#include <curses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "node.h"
#include "trie.h"

#define MAX_LINE 100

void search(trie_t *trie);

void inject_file_into_trie(trie_t *trie, char *filename, error_t *err);

int main(int argc, char **argv) {
	error_t err;
	error_init(&err);

	trie_t trie;

	trie_init(&trie);
	inject_file_into_trie(&trie, argv[1], &err);

	if (error_exist(&err)) {
		error_print(&err);
	}

	search(&trie);
	trie_deinit(&trie);
	return 0;
}

void inject_file_into_trie(trie_t *trie, char *filename, error_t *err) {
	FILE *dict = fopen(filename, "r");
	if (dict == NULL) {
		err->message = "file does not exist";
		return;
	}

	char word[MAX_LINE];
	while (fgets(word, MAX_LINE, dict) != NULL) {
		trie_add_word(trie, word);
	}

	fclose(dict);
}

void search(trie_t *trie) {
	char input[MAX_LINE], ret[MAX_LINE];

	error_t err;
	error_init(&err);

	while (true) {
		scanf("%s", input);

		trie_get_word(trie, input, ret, &err);

		if (error_exist(&err)) {
			error_print(&err);
			error_init(&err);
			continue;
		}

		printf("%s\n", ret);
	}
}
