#ifndef NODE_H
#define NODE_H

struct node_t *new_node();
struct linked_list_t *empty_list();
struct linked_list_t *linked_list(char *word);

typedef struct node_t {
	struct node_t *number_key[8];
	struct linked_list_t *front;
} node_t;

typedef struct linked_list_t {
	char *word;
	struct linked_list_t *next;
} linked_list_t;

void free_all(node_t *root);
void free_linked_list(linked_list_t *front);

#endif // NODE_H
