#include <assert.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "llist.h"

llist_t *llist_new() {
	struct llist_t *list = (struct llist_t *)malloc(sizeof(llist_t));
	return list;
}

static void copy_word(llist_t *list, char *word) {
	// otherwise will get into memory leak
	assert(list->word == NULL);

	size_t size = strlen(word) + 1;

	list->word = malloc(sizeof(char) * size);
	strncpy(list->word, word, size);
}

void llist_init(llist_t *list, char *word) {
	if (word != NULL) {
		copy_word(list, word);
	}

	list->next = NULL;
}

void llist_deinit(llist_t *list) {
	if (list->next) {
		llist_deinit(list->next);
	}

	if (list->word) {
		free(list->word);
	}

	free(list);
}

llist_t *llist_tail(llist_t *list) {
	while (list->next != NULL) {
		list = list->next;
	}

	return list;
}
