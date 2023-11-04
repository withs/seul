#include "seul/arch.h"
#include "seul/platform.h"
#include "seul/ints.h"

void av() {
	

	u8 out_isb[0x16];

	void* stdout = seul_platform_windows_get_peb()->process_parameters->standard_output;

	seul_arch_x64fastcall_syscall(8, stdout, 0, 0, 0, out_isb, "ci\n", 3, 0, 0);
}

void _start() {

	// av();

	u8 out_isb[0x16];

	void* stdout = seul_platform_windows_get_peb()->process_parameters->standard_output;

	seul_arch_x64fastcall_syscall(8, stdout, 0, 0, 0, out_isb, "ca\n", 3, 0, 0);
	//seul_arch_x64fastcall_syscall(8, stdout, 0, 0, 0, out_isb, "co\n", 3, 0, 0);
	//seul_platform_windows_syscall(8, (usize)stdout, 0, 0, 0, (usize)out_isb, (usize)"co\n", 3, 0 ,0);
	i32 a = seul_platform_windows_syscall(8, (usize)stdout, 0, 0, 0, (usize)out_isb, (usize)"ce\n", 3, 0 ,0);
	//seul_platform_windows_syscall(8, stdout, 0, 0, 0, out_isb, "co\n", 3, 0, 0);
	//seul_arch_x64fastcall_syscall2(8, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11);
}