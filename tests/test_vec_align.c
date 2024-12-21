#include <assert.h>
#include <memory.h>

#include "utils.h"

typedef struct {
	char a;
	int b;
	long double c;
} gibon;

int main() {
	gibon *v_g;
	vec_new(&v_g, 1);
	gibon g = {.a = 'x', .b = 12, .c = 1.23};
	vec_push(&v_g, g);
	g.b = 45;
	vec_push(&v_g, g);
	g.a = 'z';
	g.c = 3.14;
	vec_push(&v_g, g);
	g.a = 'y';
	vec_push(&v_g, g);

	assert(vec_len(v_g) == 4);

	const gibon ex[] = {
		{.a = 'x', .b = 12, .c = 1.23},
		{.a = 'x', .b = 45, .c = 1.23},
		{.a = 'z', .b = 45, .c = 3.14},
		{.a = 'y', .b = 45, .c = 3.14},
	};
	for (int i = 0; i < vec_len(v_g); ++i) {
		assert(v_g[i].a == ex[i].a);
		assert(v_g[i].b == ex[i].b);
		assert(v_g[i].c == ex[i].c);
	}
}
