#ifndef NODE_H
#define NODE_H

#include "llist.h"

typedef struct node_t {
	struct node_t *number_key[8];
	struct llist_t *front;
} node_t;

node_t *node_new();
void node_free_all(node_t *root);
void node_init(node_t *node);

#endif // NODE_H
