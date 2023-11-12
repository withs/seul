#ifndef SEUL_IO_H
#define SEUL_IO_H

#include "seul/data_structures.h"
#include "seul/ints.h"

struct seul_io_nibbles_to_str_result_s {
	u8 _result_buffer[0x40];
	struct seul_ds_string_view_s view;
};

struct seul_io_nibbles_to_str_result_s seul_io_nibbles_to_hex_string(usize from_int, u8 and_length);
void seul_io_stdout_print(struct seul_ds_string_view_s from_string);

#endif