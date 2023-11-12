#include "seul/io.h"
#include "seul/data_structures.h"
#include "seul/platform.h"
#include "seul/defines.h"

// NOTE: tmp impl just to allow number printing
struct seul_io_nibbles_to_str_result_s seul_io_nibbles_to_hex_string(usize from_int, u8 and_length) {

	struct seul_io_nibbles_to_str_result_s res = (struct seul_io_nibbles_to_str_result_s){ 
		._result_buffer = {'0', 'x'},
		.view = {
			.str = (u8*)&res._result_buffer,
			.length = 2,
		}
	};

	for (i8 gro = 0; gro < and_length ; gro ++ ) {

		u8 assci_base = 48;
		u8 lsb = gro*4;
		u8 msb = gro*4+4;

		u8 nibble = (from_int >> lsb) & ~(~0 << (msb-lsb));
		
		if ( nibble > 9 ) {
			assci_base = 87;
		}

		u8 cha = assci_base + nibble;
		res._result_buffer[(and_length+1)-gro] = cha;
	}

	res._result_buffer[2 + and_length + 1] = '\n';
	res.view.length += and_length + 1;

	return res;
};

void seul_io_stdout_print(struct seul_ds_string_view_s from_string) {

	static void* stdout = (void*)1;

	#if __target_windows
	stdout = seul_platform_windows_get_peb()->process_parameters->standard_output;
	#endif

	seul_platform_write(stdout, from_string);

}