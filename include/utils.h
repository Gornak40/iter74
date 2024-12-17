#pragma once

#include <stdlib.h>

#define FAIL(msg)           \
	do {                    \
		perror(msg);        \
		exit(EXIT_FAILURE); \
	} while (0);

char* read_file(const char* path);
