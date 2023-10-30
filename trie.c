#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "error.h"
#include "llist.h"
#include "node.h"
#include "trie.h"

static int get_key(char letter);

void trie_init(trie_t *trie) {
	node_init(&trie->root);
	trie->size = 1;
}

void trie_deinit(trie_t *trie) {
	node_t *nodes[trie->size];
	node_iterate(&trie->root, nodes, 0);

	for (size_t i = 0; i < trie->size; i++) {
		node_t *node = nodes[i];
		node_deinit(node);

		bool is_root = i == 0;

		if (!is_root) {
			free(node);
		}
	}
}

static node_t *fetch_next_node(trie_t *trie, node_t *node, size_t key) {
	if (node->number_key[key] != NULL) {
		return node->number_key[key];
	}

	node_t *new_node = node_new();
	trie->size++;
	node_init(new_node);

	node->number_key[key] = new_node;

	return new_node;
}

void trie_add_word(trie_t *trie, char *word) {
	node_t *node = &trie->root;

	for (int i = 0; i < strlen(word) - 1; i++) {
		int key = get_key(word[i]);
		node = fetch_next_node(trie, node, key);

		bool is_leaf = i == (strlen(word) - 2);

		if (!is_leaf) {
			continue;
		}

		node_push_word(node, word);
	}
}

int map_pressed_key_number(char c) {
	char map[] = "iojklm,.";
	size_t size = sizeof(map) / sizeof(map[0]);
	for (size_t i = 0; i < size; i++) {
		if (map[i] == c) {
			return i;
		}
	}

	return -1;
}

void trie_get_word(trie_t *trie, char *input, char *ret, error_t *err) {
	llist_t *list_pointer = NULL;
	int pound = 0;
	int done = 0;
	node_t *current = &trie->root;

	if (input[0] == 'n') {
		done = 1;
		if (list_pointer != NULL && list_pointer->next != NULL) {
			list_pointer = list_pointer->next;
			strcpy(ret, list_pointer->word);
		} else {
			err->message = "there are no more synonyms";
			return;
		}
	} else {
		list_pointer = current->words;
		for (int i = 0; i < strlen(input) - 1; i++) {
			if (current != NULL) {
				char c = input[i];
				int next_id = map_pressed_key_number(c);
				if (next_id != -1) {
					current = current->number_key[next_id];
					continue;
				}
				switch (c) {
				case ' ':
					if (pound == 0) {
						list_pointer = current->words;
					}
					pound++;
					break;
				default:
					// TODO: fix this message
					err->message = "invalid input: can only accept Integer (2 to 9) or #";
					break;
				}
			} else {
				if (done == 0) {
					done = 1;
					err->message = "not found in current dictionary.";
				}
			}
		}
	}
	if (current != NULL && current->words != NULL && pound == 0) {
		list_pointer = current->words;
		strcpy(ret, current->words->word);
	} else if (pound > 0) {
		while (list_pointer != NULL && list_pointer->next != NULL && pound > 0) {
			list_pointer = list_pointer->next;
			pound--;
		}
		if (pound == 0) {
			printf("%s\n", list_pointer->word);
		} else {
			if (done == 0) {
				done = 1;
				err->message = "not found in current dictionary.";
			}
		}
	} else {
		if (done == 0) {
			err->message = "not found in current dictionary.";
		}
	}
}

static int get_key(char letter) {
	char *map[] = {"abc", "def", "ghi", "jkl", "mno", "pqrs", "tuv", "wxyz"};

	size_t size = sizeof(map) / sizeof(map[0]);

	for (int i = 0; i < size; i++) {
		char *key = map[i];
		for (size_t j = 0; j < strlen(key); j++) {
			char c = key[j];
			if (c == letter) {
				return i;
			}
		}
	}

	error_t err;
	error_init(&err);

	err.message = malloc(sizeof(char) * 100);
	sprintf(err.message, "invalid character code in dictionary file (%d).",
					letter);

	error_panic(&err);

	return -1;
}
