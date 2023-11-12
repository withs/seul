#ifndef SEUL_DATA_STRUCTURES_H
#define SEUL_DATA_STRUCTURES_H

#include "seul/ints.h"

struct seul_ds_string_view_s {
	u8* str;
	isize length;
};

struct seul_ds_array_view_s {
	void* data;
	isize length;
};

struct seul_ds_array_view_s seul_ds_array_view_from_ptr(void* ptr, isize and_len);
struct seul_ds_string_view_s seul_ds_string_view_from_ptr(u8* str, isize and_len);


#endif