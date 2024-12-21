#pragma once

#include <stdlib.h>

#define FAIL(msg)           \
	do {                    \
		perror(msg);        \
		exit(EXIT_FAILURE); \
	} while (0);

char* read_file(const char* path);

typedef struct {
	int len;
	int cap;
} _vec_meta_t;

#define _vec_meta(v) ((_vec_meta_t*)(void*)(v)-1)

#define vec_len(v) (_vec_meta(v)->len)

#define vec_new(vp, n)                                                        \
	do {                                                                      \
		_vec_meta_t* vm = malloc(sizeof(**(vp)) * (n) + sizeof(_vec_meta_t)); \
		vm->cap = n;                                                          \
		*(vp) = (void*)(vm + 1);                                              \
	} while (0)

#define vec_free(v) free(_vec_meta(v))

#define vec_pop(v) (_vec_meta(v)->len--)

#define vec_push(vp, el)                                                              \
	do {                                                                              \
		_vec_meta_t* vm = _vec_meta(*(vp));                                           \
		if (vm->len == vm->cap) {                                                     \
			*(vp) =                                                                   \
				(void*)((_vec_meta_t*)realloc(vm, (vm->cap <<= 1) * sizeof(**(vp))) + \
						1);                                                           \
		}                                                                             \
		(*(vp))[_vec_meta(*(vp))->len++] = (el);                                      \
	} while (0)
