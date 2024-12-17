#include <stdio.h>
#include <stdlib.h>

#include "tokenizer.h"
#include "utils.h"

int main(int argc, char* argv[]) {
	if (argc != 2) {
		printf("Usage: %s file\n", *argv);
		return 1;
	}
	char* source = read_file(argv[1]);
	token_t* result = tokenize(source);

	free(result);
	free(source);
}
