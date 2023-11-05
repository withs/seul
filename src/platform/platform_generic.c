#include "seul/arch.h"
#include "seul/ints.h"
#include "seul/defines.h"
#include "seul/platform.h"

i32 seul_platform_write(void* to_fd, void* from_buff, usize with_len) {

	#if __target_windows

	u8 out_isb[0x10];

	return seul_platform_windows_syscall(8, to_fd, 0, 0, 0, out_isb, from_buff, with_len, 0, 0);
	
	#endif

	#if __target_openbsd

	return seul_platform_openbsd_syscall(4, to_fd, from_buff, with_len);
	
	#endif
	
}

void seul_platform_exit(i32 with_code) {

	#if __target_windows
	// FIXME: Both -1 and 0 make the program crash instead of killing it, again maybe its my aarch64 vm
	// https://undocumented-ntinternals.github.io/index.html?page=UserMode%2FUndocumented%20Functions%2FNT%20Objects%2FProcess%2FNtTerminateProcess.html
	// https://doxygen.reactos.org/d3/d5c/zwfuncs_8h.html#a719a7ce85358702f11dce2cd31896b4b
	seul_platform_windows_syscall(44, -1, with_code);
	#endif

	#if __target_openbsd
	seul_platform_openbsd_syscall(1, with_code);
	#endif
}