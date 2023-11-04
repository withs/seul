// #include "stdio.h"

#include "seul/ints.h"
#include "seul/defines.h"
#include "seul/platform.h"
#include "seul/arch.h"

int _start(void) {

	// printf("is macos: %d\n", __target_macos);
	// printf("is openbsd: %d\n", __target_openbsd);
	// printf("target_platform: %d\n", __target_platform);
	// printf("target_arch: %d\n", __target_arch);

	seul_arch_none();

  seul_platform_openbsd_syscall(4, 1, "helo2\n", 6);
  seul_platform_openbsd_syscall(4, 1, "helo3\n", 6);
  seul_platform_openbsd_syscall(1, 1);

	return 1;
}
