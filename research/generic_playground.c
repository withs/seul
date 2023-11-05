#include "seul/platform.h"
#include "seul/macro.h"
#include "seul/ints.h"

struct cool_s {
	i32 a;
	void* c;
	i32 b;
};

void _start() {


	struct cool_s cool = (struct cool_s){.a = 1, .b = 2};
	isize a = seul_offset_of_struct(cool_s, b);

	isize b = seul_count_of_static_array( (i32[10]){} );

	const char* text = "hello_openbsd\n";
	void* stdout = (void*)1;

	#if __target_windows	
	stdout = seul_platform_windows_get_peb()->process_parameters->standard_output;
	text = "hello_windows\n";
	#endif

	seul_platform_write(stdout, text, 14);
	seul_platform_write(stdout, ":)\n", 3);
	seul_platform_exit(0);
}
