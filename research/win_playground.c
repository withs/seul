#include "seul/arch.h"
#include "seul/platform.h"
#include "seul/ints.h"

void _start() {

	u8 out_isb[0x10];

	void* stdout = seul_platform_windows_get_peb()->process_parameters->standard_output;

	seul_arch_x64fastcall_syscall_set_call(8);
	seul_arch_x64fastcall_syscall(stdout, 0, 0, 0, out_isb, "[+] hello\n", 11, 0, 0);
	
	seul_arch_x64fastcall_syscall_set_call(8);
	seul_arch_x64fastcall_syscall(stdout, 0, 0, 0, out_isb, "seuil -o3\n:)\n", 13, 0, 0);
}