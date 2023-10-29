#include<stdlib.h>
#include <string.h>

#include "llist.h"

llist_t *llist_new() {
	struct llist_t *list = (struct llist_t *)malloc(sizeof(llist_t));
	return list;
}

void llist_init(llist_t *list, char *word) {
	if (word != NULL) {
		list->word = (char *)malloc(sizeof(char) * strlen(word));
		strncpy(list->word, word, strlen(word));
		list->word[strlen(word) - 1] = '\0';
	}
	list->next = NULL;
}

void llist_free(llist_t *list) {
	if (list->next) {
		llist_free(list->next);
	}

	if (list->word) {
		free(list->word);
	}

	free(list);
}
