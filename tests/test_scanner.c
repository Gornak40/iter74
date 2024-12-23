#include <assert.h>

#include "scanner.h"
#include "tokenizer.h"

static scn_err_t run(const char* s) {
	tokenizer_t* t = tokenizer_new();
	tokenizer_feed(t, s);
	scn_err_t err = scan_tokens(t->v_tok);
	tokenizer_free(t);
	return err;
}

int main() {
	{
		const char* s = "func a b stop";
		assert(run(s) == kScnOk);
	}
	{
		const char* s =
			"func a b stop\n"
			"func c d stop\n";
		assert(run(s) == kScnOk);
	}
	{
		const char* s = "func a b stop stop";
		assert(run(s) == kScnOutFunc);
	}
	{
		const char* s = "func a b";
		assert(run(s) == kScnPosBal);
	}
	{
		const char* s = "iter true .read stop";
		assert(run(s) == kScnOutFunc);
	}
	{
		const char* s = "=";
		assert(run(s) == kScnOutFunc);
	}
	{
		const char* s = "func a b func c d stop stop";
		assert(run(s) == kScnNestFunc);
	}
	{
		const char* s =
			"func main\n"
			"once true\n"
			"iter true\n"
			"pass true\n"
			".read\n"
			"stop\n"
			"stop\n"
			"stop\n";
		assert(run(s) == kScnBadPass);
	}
	{
		const char* s =
			"func main\n"
			"once =\n"
			"stop\n";
		assert(run(s) == kScnNoExpr);
	}
	{
		const char* s =
			"func main\n"
			"iter <-\n"
			"stop\n";
		assert(run(s) == kScnNoExpr);
	}
	{
		const char* s =
			"func main\n"
			"iter true\n"
			"once null\n"
			"pass halt\n"
			"stop\n"
			"stop\n";
		assert(run(s) == kScnNoExpr);
	}
	{
		const char* s = "func .main stop";
		assert(run(s) == kScnNoVar);
	}
	{
		const char* s = "func halt a stop";
		assert(run(s) == kScnNoVar);
	}
	{
		const char* s = "func = B stop";
		assert(run(s) == kScnNoVar);
	}
	{
		const char* s = "func + a b stop";
		assert(run(s) == kScnNoVar);
	}
}
