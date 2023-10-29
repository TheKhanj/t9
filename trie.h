#ifndef TRIE_H
#define TRIE_H

#include "node.h"

void trie_add_word(node_t *head, char *word);
void trie_get_word(char *input, node_t *current, char *ret);

#endif // TRIE_H
