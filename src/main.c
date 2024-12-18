#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"
#include "utils.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s file\n", *argv);
		return EXIT_FAILURE;
	}
	char* source = read_file(argv[1]);
	tokenizer_t* t = tokenizer_new();
	tokenizer_feed(t, source);

	tokenizer_free(t);
	free(source);
}
