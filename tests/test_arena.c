#define ARENA_BLOCK_BYTES 10

#include <assert.h>
#include <string.h>

#include "arena.h"

int main() {
	arena_t *ar = arena_new();
	{
		int *a = arena_alloc(ar, sizeof(*a) * 2);
		a[0] = 1;
		a[1] = 2;
		const int ex[] = {1, 2};
		assert(!memcmp(a, ex, sizeof(ex)));
	}
	{
		long long *b = arena_alloc(ar, sizeof(*b));
		*b = 12121212121212;
		const long long ex[] = {12121212121212};
		assert(!memcmp(b, ex, sizeof(ex)));
	}
	{
		char *c = arena_alloc(ar, sizeof(*c) * 2);
		c[0] = 'a';
		c[1] = '\0';
		assert(!strcmp(c, "a"));
	}
	arena_free(ar);
}
