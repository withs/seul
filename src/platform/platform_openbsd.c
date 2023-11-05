#include "seul/defines.h"
#include "seul/ints.h"

#include "stdarg.h"

#if __target_openbsd

// NOTE: when linking with nostdlib clang omit the openbsd signature (i guess that this is located inside the crt)
// usaly assemblu should be in arch but since those are only defines and not arch instructions it's ok atm
__asm__ (
	".section \".note.openbsd.ident\", \"a\"\n"
	".p2align 2\n"
	".long 0x8\n"
	".long 0x4\n"
	".long 0x1\n"
	".asciz \"OpenBSD\"\n"
	".long 0x0\n"
	".previous\n"
);

// NOTE: on open bsd you can't do direct syscalls since 2019, when ld.so laod your exe it mark itself/libc the only place where syscall are allowed
// so we still link with nostdlib but we link with a fake ld.so containing syscall(2), it allow to have "acces" to the syscall(2) without having the whole libc.so
// https://lwn.net/Articles/806776/
// it work on all x64 and aarch64
extern usize syscall(i32 syscall_number);

// NOTE: not very sure about that, it's used as ans alias, tried in -g3 and -O3 with both working
usize seul_platform_openbsd_syscall(i32 syscall_number, ...) {
	return syscall(syscall_number);
}

#endif