#include "seul/platform.h"
#include "seul/macro.h"
#include "seul/ints.h"
#include "seul/allocators.h"


void* stdout = (void*)1;

struct cool_s {
	i32 a;
	void* c;
	i32 b;
};


// NOTE: this code run on both open bsd and windows


struct res_s {
	u8 res[64];
	u8 len;
};
// NOTE: just testing, not real impl
struct res_s print_uint_as_hex(usize a, u8 len) {

	struct res_s r = (struct res_s){ 0 };

	r.res[0] = '0';
	r.res[1] = 'x';

	for (i8 gro = 0; gro < len ; gro ++ ) {

		u8 assci_base = 48;
		u8 lsb = gro*4;
		u8 msb = gro*4+4;

		u8 group = (a >> lsb) & ~(~0 << (msb-lsb));
		
		if ( group > 9 ) {
			assci_base = 87;
		}

		u8 cha = assci_base+group;
		r.res[(len+1)-gro] = cha;
		
	}

	seul_platform_write(stdout, &r.res, len+2);
	seul_platform_write(stdout, "\n", 1);
	
	return r;
};

int _start() {


	// struct cool_s cool = (struct cool_s){.a = 1, .b = 2};
	// isize a = seul_offset_of_struct(cool_s, b);

	// isize b = seul_count_of_static_array( (i32[10]){} );

	const char* text = "hello_openbsd\n";

	#if __target_windows	
	stdout = seul_platform_windows_get_peb()->process_parameters->standard_output;
	text = "hello_windows\n";
	#endif

	seul_platform_write(stdout, text, 14);
	seul_platform_write(stdout, ":)\n", 3);


	struct seul_allocator_mem_alloc_optional_s r = seul_platform_alloc_virtual_memory(0, 10, saop_read | saop_write);
	if (r.state == saor_ok) {
		seul_platform_write(stdout, "yes\n", 4);
	} else {
		seul_platform_write(stdout, "no\n", 3);
	}

	*(u8*)(r.address) = 123;
	print_uint_as_hex((usize)r.size, seul_size_of(void*)*2);

	seul_platform_exit(0);
	return 1;
}
