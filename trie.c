#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <string.h>

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
				switch (input[i]) {
				case 'i':
					current = current->number_key[0];
					break;
				case 'o':
					current = current->number_key[1];
					break;
				case 'j':
					current = current->number_key[2];
					break;
				case 'k':
					current = current->number_key[3];
					break;
				case 'l':
					current = current->number_key[4];
					break;
				case 'm':
					current = current->number_key[5];
					break;
				case ',':
					current = current->number_key[6];
					break;
				case '.':
					current = current->number_key[7];
					break;
				case ' ':
					if (pound == 0) {
						list_pointer = current->words;
					}
					pound++;
					break;
				default:
					// TODO: fix this message
					err->message = "invalid input: can only accept Integer (2 to 9) or #";
					return;
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
	switch (letter) {
	case 'a':
	case 'b':
	case 'c':
		return 0;
	case 'd':
	case 'e':
	case 'f':
		return 1;
	case 'g':
	case 'h':
	case 'i':
		return 2;
	case 'j':
	case 'k':
	case 'l':
		return 3;
	case 'm':
	case 'n':
	case 'o':
		return 4;
	case 'p':
	case 'q':
	case 'r':
	case 's':
		return 5;
	case 't':
	case 'u':
	case 'v':
		return 6;
	default:
		return 7;
	}
}
