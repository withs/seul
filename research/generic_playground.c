#include "seul/platform.h"
#include "seul/macro.h"
#include "seul/ints.h"
#include "seul/allocators.h"
#include "seul/data_structures.h"
#include "seul/mem.h"
#include "seul/io.h"

void* stdout = (void*)1;

struct res_s {
	u8 _buff[64];
	struct seul_ds_string_view_s view;
};
// NOTE: just testing, not real impl
struct res_s nibble_to_hex(usize a, u8 len) {

	struct res_s r = (struct res_s){ .view = {
		.str = &r._buff,
		.length = 2,
	}};

	r._buff[0] = '0';
	r._buff[1] = 'x';

	for (i8 gro = 0; gro < len ; gro ++ ) {

		u8 assci_base = 48;
		u8 lsb = gro*4;
		u8 msb = gro*4+4;

		u8 group = (a >> lsb) & ~(~0 << (msb-lsb));
		
		if ( group > 9 ) {
			assci_base = 87;
		}

		u8 cha = assci_base+group;
		r._buff[(len+1)-gro] = cha;
		r.view.length += 1;
	}

	r._buff[r.view.length + 1] = '\n';
	r.view.length += 2;
	
	return r;
};

int _start() {

	u8 hello_text[] = "hello from seul";
	seul_io_stdout_print(seul_ds_string_view_from_ptr((u8*)hello_text, seul_size_of(hello_text)));
	
	seul_io_stdout_print(seul_ds_string_view_from_ptr("\n", 1));

	struct seul_io_nibbles_to_str_result_s nib = seul_io_nibbles_to_hex_string(0xFF1133, 6);
	seul_io_stdout_print(nib.view);
	seul_io_stdout_print(seul_ds_string_view_from_ptr("\n", 1));

	struct seul_allocator_mem_alloc_optional_s m = seul_platform_alloc_virtual_memory((void*)0, 0x40, saop_read | saop_write);
	seul_io_stdout_print(seul_io_nibbles_to_hex_string((usize)m.view.data, seul_size_of(void*)*2).view);
	seul_io_stdout_print(seul_ds_string_view_from_ptr("\n", 1));
	seul_io_stdout_print(seul_io_nibbles_to_hex_string((usize)m.view.length, seul_size_of(void*)*2).view);

	seul_platform_release_virtual_memory(m.view);

	
	seul_platform_exit(0);
	return 1;
}
