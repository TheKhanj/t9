#ifndef LLIST_H
#define LLIST_H

typedef struct llist_t {
	char *word;
	struct llist_t *next;
} llist_t;

llist_t *llist_new();
void llist_free(llist_t *list);
void llist_init(llist_t *list, char *word);

#endif // LLIST_H
