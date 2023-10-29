#include <stdio.h>
#include <stdlib.h>

#include "error.h"

void error_init(error_t *err) {
	err->message = NULL;
	err->exit_code = 1;
}

bool error_exist(error_t *err) { return err->message != NULL; }

void error_print(error_t *err) { fprintf(stderr, "error: %s", err->message); }

void error_panic(error_t *err) {
	error_panic(err);
	exit(err->exit_code);
}
