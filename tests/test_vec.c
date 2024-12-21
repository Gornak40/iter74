#include <assert.h>
#include <memory.h>

#include "utils.h"

int main() {
	{
		int *v_i;
		vec_new(&v_i, 3);
		vec_push(&v_i, 1);
		vec_push(&v_i, 2);
		vec_push(&v_i, 3);
		vec_push(&v_i, 4);
		vec_pop(v_i);
		vec_push(&v_i, 5);
		vec_push(&v_i, 6);
		vec_push(&v_i, 22);

		assert(vec_len(v_i) == 6);

		const int ex[] = {1, 2, 3, 5, 6, 22};
		assert(!memcmp(v_i, ex, sizeof(ex)));
		vec_free(v_i);
	}

	{
		typedef struct {
			int x;
			long long y;
		} ipair;

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
		for (int i = 0; i < vec_len(v_p); ++i) {
			assert(v_p[i].x == ex[i].x && v_p[i].y == ex[i].y);
		}
		vec_free(v_p);
	}

	{
		typedef struct {
			char a;
			int b;
			long double c;
		} gibon;

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
		vec_free(v_g);
	}

	{
		char *v_s;
		vec_new(&v_s, 1);
		vec_push(&v_s, 'a');
		vec_push(&v_s, 'b');
		vec_push(&v_s, 'a');
		vec_push(&v_s, 'c');
		vec_push(&v_s, 'a');
		vec_push(&v_s, 'b');
		vec_push(&v_s, 'a');
		vec_push(&v_s, 'x');
		vec_pop(v_s);
		vec_pop(v_s);
		vec_push(&v_s, 'a');
		vec_push(&v_s, '\0');

		assert(vec_len(v_s) == 8);
		assert(!strcmp(v_s, "abacaba"));
	}
}
