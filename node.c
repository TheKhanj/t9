#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"
#include "node.h"

node_t *node_new() {
	node_t *node = (node_t *)malloc(sizeof(node_t));
	return node;
}

void node_init(node_t *node) {
	for (int i = 0; i < 8; i++) {
		node->number_key[i] = NULL;
	}

	node->words = NULL;
}

void node_deinit(node_t *node) {
	if (node->words) {
		llist_deinit(node->words);
	}
}

void node_iterate(node_t *node, node_t **nodes, size_t size) {
	nodes[size++] = node;

	for (int i = 0; i < 8; i++) {
		if (node->number_key[i]) {
			node_iterate(node->number_key[i], nodes, size);
		}
	}
}

void node_push_word(node_t *node, char *word) {
	if (node->words == NULL) {
		node->words = llist_new();
		llist_init(node->words, word);
		return;
	}

	llist_t *tail = llist_tail(node->words);

	tail->next = llist_new();
	llist_init(tail->next, word);
}
