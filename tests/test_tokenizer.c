#include <assert.h>

#include "tokenizer.h"

const char *s1 =
	"func add a b\n"
	"\tfunc = + a b\n"
	"stop\n";
token_typ_t t1[] = {kFunc, kId, kId, kId, kFunc, kSet, kSunc, kId, kId, kStop};

int main() {
	tokenizer_t *t = tokenizer_new();
	tokenizer_feed(t, s1);
	int l1 = sizeof(t1) / sizeof(*t1);
	assert(t->len == l1);
	for (int i = 0; i < l1; ++i) {
		assert(t->tokens[i].type == t1[i]);
	}
	tokenizer_free(t);
}
