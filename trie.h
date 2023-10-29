#ifndef TRIE_H
#define TRIE_H

#include "error.h"
#include "node.h"

#include <stddef.h>

typedef struct trie_t {
	node_t root;
	size_t size;
} trie_t;

void trie_init(trie_t *trie);
void trie_deinit(trie_t *trie);

void trie_add_word(trie_t *trie, char *word);
void trie_get_word(trie_t *trie, char *input, char *ret, error_t *err);

#endif // TRIE_H
