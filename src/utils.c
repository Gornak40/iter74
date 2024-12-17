#include "utils.h"

#include <fcntl.h>
#include <stdio.h>
#include <unistd.h>

char* read_file(const char* path) {
	int fd = open(path, O_RDONLY);
	if (fd == -1) {
		FAIL("Failed read_file");
	}

	off_t file_size = lseek(fd, 0, SEEK_END);
	if (file_size == -1) {
		FAIL("Failed read_file");
	}
	char* data = malloc(file_size);

	lseek(fd, 0, SEEK_SET);
	if (read(fd, data, file_size) == -1) {
		FAIL("Failed read_file");
	}
	data[file_size] = '\0';

	return data;
}
