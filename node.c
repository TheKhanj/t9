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
	node->front = NULL;
}

void node_iterate(node_t *node, node_t **nodes, size_t size) {
	nodes[size++] = node;

	for (int i = 0; i < 8; i++) {
		if (node->number_key[i]) {
			node_iterate(node->number_key[i], nodes, size);
		}
	}
}
