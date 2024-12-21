#include <stdio.h>
#include <stdlib.h>

#include "scanner.h"
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

	scn_err_t err = scan_tokens(t->v_tok);
	if (err) {
		fprintf(stderr, "Scan failed: %s\n", scan_error(err));
		return EXIT_FAILURE;
	}

	tokenizer_free(t);
	free(source);
}
