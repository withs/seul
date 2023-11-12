#include "seul/data_structures.h"
#include "seul/ints.h"

struct seul_ds_array_view_s seul_ds_array_view_from_ptr(void* ptr, isize and_len) {
	return (struct seul_ds_array_view_s) {
		.data = ptr,
		.length = and_len,
	};
}

