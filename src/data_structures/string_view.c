#include "seul/ints.h"
#include "seul/data_structures.h"

struct seul_ds_string_view_s seul_ds_string_view_from_ptr(u8* str, isize and_len) {
	return (struct seul_ds_string_view_s) {
		.str = str,
		.length = and_len,
	};
}
