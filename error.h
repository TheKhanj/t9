#ifndef ERROR_H
#define ERROR_H

#include <stdbool.h>

typedef struct error_t {
	char *message;
	int code;
} error_t;

void error_init(error_t *err);
bool error_exist(error_t *err);
void error_print(error_t *err);
void error_panic(error_t *err);

#endif // ERROR_H
