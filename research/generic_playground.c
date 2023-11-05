#include "seul/platform.h"

void _start() {

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
