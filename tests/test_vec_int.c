#include <assert.h>
#include <memory.h>

#include "utils.h"

int main() {
	int *arr;
	vec_new(&arr, 3);
	vec_push(&arr, 1);
	vec_push(&arr, 2);
	vec_push(&arr, 3);
	vec_push(&arr, 4);
	vec_pop(arr);
	vec_push(&arr, 5);
	vec_push(&arr, 6);
	vec_push(&arr, 22);

	assert(vec_len(arr) == 6);

	const int ex[] = {1, 2, 3, 5, 6, 22};
	assert(!memcmp(arr, ex, sizeof(ex)));
}
