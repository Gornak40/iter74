#include <assert.h>

#include "tokenizer.h"
#include "utils.h"

const char *s1 =
	"func add a b\n"
	"\tfunc = + a b\n"
	"stop\n";
token_typ_t t1[] = {kFunc, kId, kId, kId, kFunc, kSet, kSunc, kId, kId, kStop};

int main() {
	tokenizer_t *t = tokenizer_new();
	tokenizer_feed(t, s1);
	int l1 = sizeof(t1) / sizeof(*t1);
	assert(vec_len(t->v_tok) == l1);
	for (int i = 0; i < l1; ++i) {
		assert(t->v_tok[i].type == t1[i]);
	}
	tokenizer_free(t);
}
