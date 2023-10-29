#ifndef NODE_H
#define NODE_H

#include <stdlib.h>

#include "llist.h"

typedef struct node_t {
	struct node_t *number_key[8];
	struct llist_t *front;
} node_t;

node_t *node_new();
void node_init(node_t *node);
void node_iterate(node_t *node, node_t **nodes, size_t size);

#endif // NODE_H
