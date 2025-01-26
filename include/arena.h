#pragma once

#ifndef ARENA_BLOCK_BYTES
// 1MB block size
#define ARENA_BLOCK_BYTES 0x100000
#endif

typedef struct {
	char *mem;
	char *mptr;
	struct arena_t *nxt;
} arena_t;

arena_t *arena_new();

void arena_free(arena_t *ar);

void *arena_alloc(arena_t *ar, int size);
