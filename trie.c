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
	// TODO: fix this, size is not correct
	node_t *nodes[trie->size];
	node_iterate(&trie->root, nodes, 0);

	for (size_t i = 0; i < trie->size; i++) {
		node_t *node = nodes[i];
		if (node->front) {
			llist_free(node->front);
		}

		bool is_root = i == 0;

		if (!is_root) {
			free(node);
		}
	}
}

void trie_add_word(trie_t *trie, char *word) {
	llist_t *temp;
	node_t *head = &trie->root;

	for (int i = 0; i < strlen(word) - 1; i++) {
		int key = get_key(word[i]);
		if (head->number_key[key] != NULL) {
			head = head->number_key[key];
		} else {
			node_t *node = node_new();
			node_init(node);

			head->number_key[key] = node;
			trie->size++;
			head = node;
		}

		if (i != strlen(word) - 2) {
			continue;
		}

		if (head->front == NULL) {
			head->front = llist_new();
			llist_init(head->front, word);
		} else {
			temp = head->front;
			while (temp->next != NULL)
				temp = temp->next;

			temp->next = llist_new();
			llist_init(temp->next, word);
		}
	}
}

void trie_get_word(trie_t *trie, char *input, char *ret) {
	llist_t *listPointer = NULL;
	int pound = 0;
	int done = 0;
	node_t *current = &trie->root;

	if (input[0] == 'n') {
		done = 1;
		if (listPointer != NULL && listPointer->next != NULL) {
			listPointer = listPointer->next;
			strcpy(ret, listPointer->word);
		} else {
			printf("There are no more T9onyms\n");
			return;
		}
	} else {
		listPointer = current->front;
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
						listPointer = current->front;
					}
					pound++;
					break;
				default:
					printf("Invalid input: can only accept Integer (2 to 9)  or #\n");
					return;
				}
			} else {
				if (done == 0) {
					done = 1;
					printf("Not found in current dictionary.\n");
				}
			}
		}
	}
	if (current != NULL && current->front != NULL && pound == 0) {
		listPointer = current->front;
		strcpy(ret, current->front->word);
	} else if (pound > 0) {
		while (listPointer != NULL && listPointer->next != NULL && pound > 0) {
			listPointer = listPointer->next;
			pound--;
		}
		if (pound == 0) {
			printf("%s\n", listPointer->word);
		} else {
			if (done == 0) {
				done = 1;
				printf("Not found in current dictionary.\n");
			}
		}
	} else {
		if (done == 0) {
			printf("Not found in current dictionary.\n");
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
