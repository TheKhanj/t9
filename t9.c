#include <assert.h>
#include <ctype.h>
#include <curses.h>
#include <ncurses.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"

#define MAX_LINE 100

void build_trie(node_t *head, char *word);
int get_key(char letter);
void search(node_t *root);

int main(int argc, char **argv) {
	FILE *dict = fopen(argv[1], "r");
	char word[MAX_LINE];
	node_t *root = new_node();
	node_t *temp;
	if (dict == NULL) {
		fprintf(stderr, "File does not exist\n");
		return 1;
	}
	while (fgets(word, MAX_LINE, dict) != NULL) {
		temp = root;
		build_trie(temp, word);
	}
	fclose(dict);
	search(root);
	free_all(root);
	return 0;
}

int get_key(char letter) {
	switch (letter) {
	case 'a':
	case 'b':
	case 'c':
		return 0;
	case 'd':
	case 'e':
	case 'f':
		return 1;
	case 'g':
	case 'h':
	case 'i':
		return 2;
	case 'j':
	case 'k':
	case 'l':
		return 3;
	case 'm':
	case 'n':
	case 'o':
		return 4;
	case 'p':
	case 'q':
	case 'r':
	case 's':
		return 5;
	case 't':
	case 'u':
	case 'v':
		return 6;
	default:
		return 7;
	}
}

void build_trie(node_t *head, char *word) {
	linked_list_t *temp;
	for (int i = 0; i < strlen(word) - 1; i++) {
		int key = get_key(word[i]);
		if (head->number_key[key] != NULL) {
			head = head->number_key[key];
		} else {
			head->number_key[key] = new_node();
			head = head->number_key[key];
		}
		if (i == strlen(word) - 2) {
			if (head->front == NULL) {
				head->front = linked_list(word);
			} else {
				temp = head->front;
				while (temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = linked_list(word);
			}
		}
	}
}

void get_word(char *input, node_t *current, char *ret) {
	linked_list_t *listPointer = NULL;
	int pound = 0;
	int done = 0;

	if (input[0] == 'n') {
		done = 1;
		if (listPointer != NULL && listPointer->next != NULL) {
			listPointer = listPointer->next;
			strcpy(ret, listPointer->word);
		} else {
			printf("There are no more T9onyms\n");
			return;
		}
	} else {
		listPointer = current->front;
		for (int i = 0; i < strlen(input) - 1; i++) {
			if (current != NULL) {
				switch (input[i]) {
				case 'i':
					current = current->number_key[0];
					break;
				case 'o':
					current = current->number_key[1];
					break;
				case 'j':
					current = current->number_key[2];
					break;
				case 'k':
					current = current->number_key[3];
					break;
				case 'l':
					current = current->number_key[4];
					break;
				case 'm':
					current = current->number_key[5];
					break;
				case ',':
					current = current->number_key[6];
					break;
				case '.':
					current = current->number_key[7];
					break;
				case ' ':
					if (pound == 0) {
						listPointer = current->front;
					}
					pound++;
					break;
				default:
					printf("Invalid input: can only accept Integer (2 to 9)  or #\n");
					return;
				}
			} else {
				if (done == 0) {
					done = 1;
					printf("Not found in current dictionary.\n");
				}
			}
		}
	}
	if (current != NULL && current->front != NULL && pound == 0) {
		listPointer = current->front;
		strcpy(ret, current->front->word);
	} else if (pound > 0) {
		while (listPointer != NULL && listPointer->next != NULL && pound > 0) {
			listPointer = listPointer->next;
			pound--;
		}
		if (pound == 0) {
			printf("%s\n", listPointer->word);
		} else {
			if (done == 0) {
				done = 1;
				printf("Not found in current dictionary.\n");
			}
		}
	} else {
		if (done == 0) {
			printf("Not found in current dictionary.\n");
		}
	}
}

void search(node_t *root) {
	cbreak();
	echo();
	initscr();
	char input[MAX_LINE], ret[MAX_LINE];
	int pos = 0;

	while (true) {
		char x = getch();
		input[pos] = x;
		input[pos + 1] = 0;

		if (x == EOF) {
			pos = 0;
		} else {
			get_word(input, root, ret);
			pos++;
		}
		refresh();
	}
}
