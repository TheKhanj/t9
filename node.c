#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

struct node_t *new_node() {
	struct node_t *trie = (node_t *)malloc(sizeof(node_t));
	for (int i = 0; i < 8; i++) {
		trie->number_key[i] = NULL;
	}
	trie->front = NULL;
	return trie;
}

struct linked_list_t *empty_list() {
	struct linked_list_t *list =
			(struct linked_list_t *)malloc(sizeof(linked_list_t));
	list->word = NULL;
	list->next = NULL;
	return list;
}

struct linked_list_t *linked_list(char *word) {
	struct linked_list_t *list =
			(struct linked_list_t *)malloc(sizeof(struct linked_list_t));
	list->word = (char *)malloc(sizeof(char) * strlen(word));
	strncpy(list->word, word, strlen(word));
	list->word[strlen(word) - 1] = '\0';
	list->next = NULL;
	return list;
}

void free_all(node_t *root) {
	for (int i = 0; i < 8; i++) {
		if (root->number_key[i]) {
			free_all(root->number_key[i]);
		}
	}
	if (root->front) {
		free_linked_list(root->front);
	}
	free(root);
}

void free_linked_list(linked_list_t *front) {
	if (front->next) {
		free_linked_list(front->next);
	}
	free(front->word);
	free(front);
}
