#ifndef SEUL_ARCH_H
#define SEUL_ARCH_H

#include "seul/defines.h"
#include "seul/ints.h"

enum arch_e {
	arch_none,
	arch_aarch64,
	arch_x64,
	arch_i386,
};

#if __arch_aarch64
	#define __target_arch ((enum arch_e)arch_aarch64)
#elif __arch_x64
	#define __target_arch ((enum arch_e)arch_x64)
#elif __arch_i386
	#define __target_arch ((enum arch_e)arch_i386)
#else
	#define __target_arch ((enum arch_e)arch_none)
#endif


void seul_arch_none(void);


#if __arch_x64
void* seul_arch_x64_read_gs(usize with_offset);
i32 seul_arch_x64fastcall_syscall(usize number, ...);
#endif

#endif