#ifndef TRIE_H
#define TRIE_H

#include "node.h"

#include <stddef.h>

typedef struct trie_t {
	node_t root;
	// TODO: fix this
	size_t size;
} trie_t;

void trie_init(trie_t *trie);
void trie_deinit(trie_t *trie);

void trie_add_word(trie_t *trie, char *word);
void trie_get_word(trie_t *trie, char *input, char *ret);

#endif // TRIE_H
