// William Thing
// CSE374 Homework 5
// t9.c
//
// This t9 program takes in a file of words
// that creates differen paths in a Trie for
// given words. It has the function to search
// the Trie with t9 number keys to find
// specific words.

#include "Node.h"
#include <assert.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE 100 // maximum character for a single line

void buildTrie(Node *head, char *word);
int getKey(char letter);
void search(Node *root);

int main(int argc, char **argv) {
	FILE *dict = fopen(argv[1], "r");
	char word[MAX_LINE];
	Node *root = newNode(); // pointer to main root of Trie
	Node *temp;
	if (dict == NULL) {
		fprintf(stderr, "File does not exist\n");
		return 1;
	}
	while (fgets(word, MAX_LINE, dict) != NULL) {
		temp = root;
		buildTrie(temp, word);
	}
	fclose(dict);
	search(root);
	freeEverything(root);
	return 0;
}

// post: takes in a letter and returns the corresponding
// 	 t9 key.
int getKey(char letter) {
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

//	post: Takes in dictionary word and top of Trie.
// 	      Builds the Trie from top to bottom pathed
//            by the given word. Given word is saved to the last
//	      path of the key Node for each word. Multiple
//	      words can be stored in the same Node.
void buildTrie(Node *head, char *word) {
	LinkedList *temp;
	for (int i = 0; i < strlen(word) - 1; i++) {
		int key = getKey(word[i]);
		if (head->numberKey[key] != NULL) {
			head = head->numberKey[key];
		} else {
			head->numberKey[key] = newNode();
			head = head->numberKey[key];
		}
		if (i == strlen(word) - 2) {
			if (head->front == NULL) {
				head->front = linkedList(word);
			} else {
				temp = head->front;
				while (temp->next != NULL) {
					temp = temp->next;
				}
				temp->next = linkedList(word);
			}
		}
	}
}

void get_word(char *input, Node *current, char *ret) {
	LinkedList *listPointer = NULL;
	int pound = 0;
	int done = 0;
	// Exit the program if User inputs 'exit'

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
					current = current->numberKey[0];
					break;
				case 'o':
					current = current->numberKey[1];
					break;
				case 'j':
					current = current->numberKey[2];
					break;
				case 'k':
					current = current->numberKey[3];
					break;
				case 'l':
					current = current->numberKey[4];
					break;
				case 'm':
					current = current->numberKey[5];
					break;
				case ',':
					current = current->numberKey[6];
					break;
				case '.':
					current = current->numberKey[7];
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
	} else if (pound > 0) { // User input of #(s)
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

//	post: Takes given Trie and searches for the word associated
//	      with the User's input. If '#' is entered then it
//     	      will search for other appropiate options for the same
//	      t9 key entry. If exit is entered by the User, the program
//	      will immediately exit.
//	      Valid User input is 2-9 integer keys and '#' option.
void search(Node *root) {
	char input[MAX_LINE], ret[MAX_LINE];

	while (fgets(input, MAX_LINE, stdin)) {
		get_word(input, root, ret);
		printf("%s\n", ret);
	}
}
