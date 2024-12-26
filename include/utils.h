#pragma once

#include <stdalign.h>
#include <stdio.h>
#include <stdlib.h>

#define FAIL(msg)           \
	do {                    \
		perror(msg);        \
		exit(EXIT_FAILURE); \
	} while (0);

#define DBG(msg, ...) fprintf(stderr, "[DBG] " msg "\n", __VA_ARGS__)

char* read_file(const char* path);

typedef struct {
	int len;
	int cap;
} _vec_meta_t;

#define _vec_msz(v) \
	(sizeof(_vec_meta_t) >= _Alignof(*(v)) ? sizeof(_vec_meta_t) : _Alignof(*(v)))

#define _vec_meta(v) ((_vec_meta_t*)((char*)(void*)(v)-_vec_msz(v)))

#define vec_len(v) (_vec_meta(v)->len)

#define vec_new(vp, n)                                        \
	do {                                                      \
		int vms = _vec_msz(*vp);                              \
		_vec_meta_t* vm = malloc(sizeof(**(vp)) * (n) + vms); \
		*vm = (_vec_meta_t){.len = 0, .cap = n};              \
		*(vp) = (void*)((char*)(void*)vm + vms);              \
	} while (0)

#define vec_free(v) free(_vec_meta(v))

#define vec_pop(v) (_vec_meta(v)->len--)

#define vec_push(vp, el)                                                                 \
	do {                                                                                 \
		int vms = _vec_msz(*vp);                                                         \
		_vec_meta_t* vm = _vec_meta(*(vp));                                              \
		if (vm->len == vm->cap) {                                                        \
			*(vp) = (void*)((char*)realloc(vm, (vm->cap <<= 1) * sizeof(**(vp)) + vms) + \
							vms);                                                        \
		}                                                                                \
		(*(vp))[_vec_meta(*(vp))->len++] = (el);                                         \
	} while (0)
