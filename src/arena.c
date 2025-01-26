#include "arena.h"

#include <assert.h>
#include <stdlib.h>

arena_t *arena_new() {
	arena_t *ar = calloc(sizeof(*ar), 1);
	ar->mem = malloc(ARENA_BLOCK_BYTES);
	ar->mptr = ar->mem;
	ar->nxt = NULL;
	return ar;
}

void arena_free(arena_t *ar) {
	if (ar == NULL) {
		return;
	}
	free(ar->mem);
	arena_free((arena_t *)ar->nxt);
	free(ar);
}

void *arena_alloc(arena_t *ar, int size) {
	assert(size <= ARENA_BLOCK_BYTES);
	for (arena_t *it = ar; it != NULL; ++it) {
		if (it->mptr - it->mem + size <= ARENA_BLOCK_BYTES) {
			void *res = it->mptr;
			it->mptr += size;
			return res;
		}
	}
	arena_t *nar = arena_new();	 // TODO: fix it
	ar->nxt = (struct arena_t *)nar;
	nar->mptr += size;
	return nar->mem;
}
