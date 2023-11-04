#include "seul/arch.h"
#include "seul/platform.h"
#include "seul/defines.h"
#include "seul/ints.h"

#include "stdarg.h"

#if __target_windows
struct seul_platform_windows_process_environment_block_s* seul_platform_windows_get_peb() {
	return (struct seul_platform_windows_process_environment_block_s*)seul_arch_x64_read_gs(0x60);
}

// NOTE: can do better but i can't manage to pass args without having them defined it make it look like popo and the asm generated is shit too...
// like if i do fn(usize syscall_number, ...)
// it allocate stack to store the arg and then the stack is not sync for the next call
// on the openbsd version it work because it generate a simple tailcall and not a ral call with args
// FIXME: i'll find something better for sure
// i32 seul_platform_windows_syscall(usize syscall_number, usize a, usize b, usize c, usize d, usize e, usize f, usize g, usize h, usize i) {

// 	#if __arch_x64
// 	return seul_arch_x64fastcall_syscall(syscall_number, a, b, c, d, e, f, g, h, i);
// 	#endif

// 	return 0;
// }


// NOTE: Is it better than above ? idk but its was fun to experiment, even if no asm should be in platform_*
// this function would have if guard for different arch anyway and the problem will probaby be the same for aarch64
// next time gimme a tailcall clang and i would not have to do it ^^
__attribute__((naked))
i32 seul_platform_windows_syscall(usize syscall_number, ...){
	#if __arch_x64
	asm volatile (
		"jmp seul_arch_x64fastcall_syscall\n\t"
		"ret\n\t"
	); 
	#endif
}
#endif

