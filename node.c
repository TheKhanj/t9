#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"
#include "node.h"

node_t *node_new() {
	node_t *trie = (node_t *)malloc(sizeof(node_t));
	return trie;
}

void node_init(node_t *node) {
	for (int i = 0; i < 8; i++) {
		node->number_key[i] = NULL;
	}
	node->front = NULL;
}

void node_free_all(node_t *root) {
	for (int i = 0; i < 8; i++) {
		if (root->number_key[i]) {
			node_free_all(root->number_key[i]);
		}
	}

	if (root->front) {
		llist_free(root->front);
	}

	free(root);
}
