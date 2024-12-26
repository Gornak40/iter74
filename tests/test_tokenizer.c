#include <assert.h>

#include "tokenizer.h"
#include "utils.h"

static void run(const char *s, const token_typ_t *tp, int len) {
	tokenizer_t *t = tokenizer_new();
	tokenizer_feed(t, s);
	assert(vec_len(t->v_tok) == len);
	for (int i = 0; i < len; ++i) {
		assert(t->v_tok[i].type == tp[i]);
	}
	tokenizer_free(t);
}

#define RUN(s, t) run((s), (t), sizeof(t) / sizeof(*(t)))

int main() {
	{
		const char *s =
			"func add a b\n"
			"\tfunc= + a b\n"
			"stop\n";
		const token_typ_t t[] = {
			kFunc, kId, kId, kId, kSetFunc, kSunc, kId, kId, kStop,
		};
		RUN(s, t);
	}
	{
		const char *s =
			"func main\n"
			"n= .read\n"
			"A= .Heap n\n"
			"i= null\n"
			"iter < i n\n"
			"I= + A i\n"
			"I<- .read\n"
			"i= ++ i\n"
			"stop\n"
			"stop\n";
		const token_typ_t t[] = {
			kFunc, kId,		  kSetId, kCall,  kSetPId, kPCall,	kId,   kSetId,
			kNull, kIter,	  kSunc,  kId,	  kId,	   kSetPId, kSunc, kPId,
			kId,   kStorePId, kCall,  kSetId, kSunc,   kId,		kStop, kStop,
		};
		RUN(s, t);
	}
}
