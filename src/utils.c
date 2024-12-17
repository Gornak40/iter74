#include "utils.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

typedef struct {
	int sz;
	int cap;
} vec_meta_t;

void* vec_alloc(int cap, int sz1) {
	vec_meta_t vm = (vec_meta_t){.sz = 0, .cap = cap};
	char* data = malloc(cap * sz1 + sizeof(vm));
	return data + sizeof(vm);
}

void vec_free(void* vec) { free((char*)vec - sizeof(vec_meta_t)); }

char* read_file(const char* path) {
	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		FAIL("Failed read_file");
	}

	off_t file_size = lseek(fd, 0, SEEK_END);
	if (file_size == -1) {
		FAIL("Failed read_file");
	}
	char* data = malloc(file_size + 1);

	lseek(fd, 0, SEEK_SET);
	if (read(fd, data, file_size) == -1) {
		FAIL("Failed read_file");
	}
	data[file_size] = '\0';

	return data;
}
