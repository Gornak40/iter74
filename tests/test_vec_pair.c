#include <assert.h>
#include <memory.h>

#include "utils.h"

typedef struct {
	int x;
	long long y;
} ipair;

int main() {
	ipair *v_p;
	vec_new(&v_p, 1);
	ipair p = (ipair){.x = 1, .y = 2};
	vec_push(&v_p, p);
	vec_pop(v_p);
	vec_push(&v_p, p);
	p.x = 100500;
	vec_push(&v_p, p);
	p.x = -1;
	p.y = 4;
	vec_push(&v_p, p);

	assert(vec_len(v_p) == 3);

	const ipair ex[] = {{.x = 1, .y = 2}, {.x = 100500, .y = 2}, {.x = -1, .y = 4}};
	assert(!memcmp(v_p, ex, sizeof(ex)));
}
